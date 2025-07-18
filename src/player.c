#include <stdlib.h>
#include "gba.h"
#include "player.h"
#include "collision.h"
#include "data/include/sprite_data.h"
#include "data/include/animation_data.h"

#define DEFAULT_ACCEL      FIXED8(0, 10)
#define DEFAULT_DECEL      FIXED8(0, 128)
#define DEFAULT_FRIC       FIXED8(0, 10)
#define DEFAULT_AIR_ACCEL  FIXED8(0, 24)
#define DEFAULT_MAXSPD     FIXED8(5, 0)
#define DEFAULT_MAXVERTSPD FIXED8(14, 0)

static playerCharData playerCharTable[NUM_OF_PLAYER_CHARS] = {
    [CHAR_TETO] = {teto_pal, (u32)_sizeof_teto_pal, animTeto, 5, 20}
};

static int animDuration;

static fixed8 camLeftBorder     = FIXED8(113, 0);
static fixed8 camRightBorder    = FIXED8(125, 0);
static fixed8 camTopBorder      = FIXED8(57, 0);
static fixed8 camVerticalPoint  = FIXED8(79, 0);
static fixed8 camBottomBorder   = FIXED8(101, 0);

static fixed8 gravity = FIXED8(0, 53);

static fixed8 slopeFactorNormal   = FIXED8(0, 52);
//static fixed8 slopeFactorRollup   = FIXED8(0, 20);
//static fixed8 slopeFactorRolldown = FIXED8(0, 80);

static fixed8 debugModeAcc = FIXED8(0, 30);

/*==========PRIVATE FUNCTIONS===================*/
INLINE void normal_slope_force(Player *player);
INLINE void normal_move_right(Player *player);
INLINE void normal_decelerate_right(Player *player);
INLINE void normal_move_left(Player *player);
INLINE void normal_decelerate_left(Player *player);
INLINE void normal_friction(Player *player);
static void normal_camera_follow(Player *player, Camera *camera);
static void normal_ground_collision(Player *player, const Stage *stage);
static void normal_walls_collision(Player *player, const Stage *stage);

INLINE void airborne_move_right(Player *player);
INLINE void airborne_move_left(Player *player);
INLINE void airborne_airdrag(Player *player);
INLINE void airborne_gravity(Player *player);
static void airborne_camera_follow(Player *player, Camera *camera);
static void airborne_collision(Player *player, const Stage *stage);

static void debug_mode_move(Player *player);

INLINE void flagged_tile_check(Player *player, const SolidTile *choosenTile);
INLINE void bounds_collision(Player *player, const Camera *camera);
INLINE void update_speed(Player *player);
INLINE void update_position(Player *player);


/*=============FUNCTIONS=========================*/

Player *player_create(fixed8 xPos, fixed8 yPos, playerState state, playerCharacter character, struct SpriteListNode **sprNode)
{
    Player *player;
    playerCharData charData;

    player = (Player *)calloc(1, sizeof(Player));

    charData = playerCharTable[character];

    player->xPos = xPos;
    player->yPos = yPos;
    player->state = state;

    player->width  = charData.width;
    player->height = charData.height;
    player->pushRadius = player->width + 6;
    player->accel = DEFAULT_ACCEL;
    player->decel = DEFAULT_DECEL;
    player->fric = DEFAULT_FRIC;
    player->airAccel = DEFAULT_AIR_ACCEL;
    player->maxSpd = DEFAULT_MAXSPD;
    player->maxVerticSpd = DEFAULT_MAXVERTSPD;

    //sprite load
    player->sprite = sprite_create(sprNode, 0, 0, 0, 0, 0, 5, 1, (ObjShape*)0);
    player->anim = charData.playerAnim;

    palette_load(charData.palData, charData.palDataLenght, PAL_OAM_INDEX);

    sprite_set_animation(player->sprite, &player->anim[ANIM_IDLE]);

    return player;
}

void player_routine(Player *player, Camera *camera, const Stage *stage)
{
    switch (player->state)
    {
        case STATE_NORMAL:

            player->isPushing = FALSE;

            normal_slope_force(player);

            if (key_is_down(KEY_RIGHT)) {

                if (player->groundSpeed < 0) {
                    normal_decelerate_right(player);
                }
                
                normal_move_right(player);

            }
            if (key_is_down(KEY_LEFT)) {

                if (player->groundSpeed > 0) {
                    normal_decelerate_left(player);
                }
                
                normal_move_left(player);

            }
            if (!key_is_down(KEY_RIGHT | KEY_LEFT)) {
                normal_friction(player);
            }

            update_speed(player);
            
            normal_walls_collision(player, stage);

            update_position(player);

            normal_ground_collision(player, stage);

            normal_camera_follow(player, camera);
        break;

        case STATE_ROLLING:

        break;

        case STATE_AIRBORNE:

            if (key_is_down(KEY_RIGHT)) {
                airborne_move_right(player);
            }
            if (key_is_down(KEY_LEFT)) {
                airborne_move_left(player);
            }
            
            airborne_airdrag(player);

            update_position(player);
            
            airborne_gravity(player);

            airborne_collision(player, stage);

            airborne_camera_follow(player, camera);
        break;

        case STATE_DEBUG:
            
            debug_mode_move(player);
            
            normal_camera_follow(player, camera);
        break;
    }

    bounds_collision(player, camera);

}

void player_animate(Player *player, Camera *camera)
{
    if (key_is_down(KEY_RIGHT))
        player->sprite->hFlip = FALSE;
    if (key_is_down(KEY_LEFT))
        player->sprite->hFlip = TRUE;

    player->sprite->xPos = fixed8_to_int(player->xPos - camera->xPos);
    player->sprite->yPos = fixed8_to_int(player->yPos - camera->yPos);

    if (!player->isPushing)
    {
        animDuration = mf_max(0, 8 - mf_abs(fixed8_to_int(player->groundSpeed)));
    
        if (mf_abs(player->groundSpeed) >= player->maxSpd) {
            sprite_set_animation(player->sprite, &player->anim[ANIM_RUN]);
        } 
        else if (player->groundSpeed != 0) {
            sprite_set_animation(player->sprite, &player->anim[ANIM_WALK]);
        }
        else {
            sprite_set_animation(player->sprite, &player->anim[ANIM_IDLE]);
            animDuration = 0;
        }
    }

    sprite_render_animation(player->sprite, animDuration);
}

void player_destroy(Player *player)
{
    free(player);
    player = NULL;
}

/*=================PRIVATE FUNCTIONS==========================*/

INLINE void normal_slope_force(Player *player)
{
    fixed8 slopeFactor = (slopeFactorNormal * -angle_sin(player->groundAngle)) >> 8;
    if (player->groundSpeed != 0 || slopeFactor >= FIXED8(0, 13))
        player->groundSpeed -= slopeFactor;
}

INLINE void normal_move_right(Player *player)
{
    if (player->groundSpeed < player->maxSpd) {
        player->groundSpeed += player->accel;
        if (player->groundSpeed >= player->maxSpd) {
            player->groundSpeed = player->maxSpd;
        }
    }
}

INLINE void normal_decelerate_right(Player *player)
{
    player->groundSpeed += player->decel;
    if (player->groundSpeed >= 0)
        player->groundSpeed = FIXED8(0, 128);
}

INLINE void normal_move_left(Player *player)
{
    if (player->groundSpeed > -player->maxSpd) {
        player->groundSpeed -= player->accel;
        if (player->groundSpeed <= -player->maxSpd) {
            player->groundSpeed = -player->maxSpd;
        }
    }
}

INLINE void normal_decelerate_left(Player *player)
{
    player->groundSpeed -= player->decel;
    if (player->groundSpeed <= 0)
        player->groundSpeed = -FIXED8(0, 128);
}

INLINE void normal_friction(Player *player)
{
    player->groundSpeed -= mf_min(mf_abs(player->groundSpeed), player->fric) * mf_sign(player->groundSpeed);
}

static void normal_camera_follow(Player *player, Camera *camera)
{
    fixed8 rightBorder   = camera->xPos + camRightBorder;
    fixed8 leftBorder    = camera->xPos + camLeftBorder;
    fixed8 verticalPoint = camera->yPos + camVerticalPoint;

    fixed8 verticalPointCap = player->groundSpeed >= FIXED8(8, 0) ? FIXED8(22, 0) : FIXED8(4, 0);

    fixed8 playerTargetX = player->xPos;
    fixed8 playerTargetY = player->yPos;

    camera->xSpeed = 0;
    camera->ySpeed = 0;

    if (playerTargetX > rightBorder)
        camera->xSpeed += playerTargetX - rightBorder;
    else if (playerTargetX < leftBorder)
        camera->xSpeed -= leftBorder - playerTargetX;
    
    if (playerTargetY != verticalPoint) {
        camera->ySpeed += playerTargetY - verticalPoint;
    }

    if (mf_abs(camera->ySpeed) > verticalPointCap) {
        camera->ySpeed = verticalPointCap * mf_sign(camera->ySpeed);
    }
}

static void normal_ground_collision(Player *player, const Stage *stage)
{
    int x = fixed8_to_int(player->xPos);
    int y = fixed8_to_int(player->yPos) + player->height;

    SolidTile solidTileA = collision_find_vertical_tile(x - player->width, y, stage, COLL_DOWN);
    SolidTile solidTileB = collision_find_vertical_tile(x + player->width, y, stage, COLL_DOWN);

    SolidTile choosenTile = solidTileA.distance <= solidTileB.distance ? solidTileA : solidTileB;

    if (choosenTile.distance > mf_min(mf_abs(fixed8_to_int(player->xSpeed)) + 4, 14)) {
        player->state = STATE_AIRBORNE;
        return;
    }
    player->yPos += FIXED8(choosenTile.distance, 0);

    player->groundAngle = choosenTile.angle;

    flagged_tile_check(player, &choosenTile);
}

static void normal_walls_collision(Player *player, const Stage *stage)
{
    if (player->groundSpeed == 0) return;

    int yoffset = 8 * (player->groundAngle == 0);
    
    int y = fixed8_to_int(player->yPos + player->ySpeed) + yoffset;

    //check for right wall collision
    if (player->groundSpeed > 0)
    {
        int x = fixed8_to_int(player->xPos + player->xSpeed) + player->pushRadius;

        SolidTile wall = collision_find_horizontal_tile(x, y, stage, COLL_RIGHT);

        if (wall.distance > 0) return;

        player->xSpeed += FIXED8(wall.distance, 0);
        player->groundSpeed = 0;
    }
    else if (player->groundSpeed < 0)
    {
        int x = fixed8_to_int(player->xPos + player->xSpeed) - player->pushRadius;

        SolidTile wall = collision_find_horizontal_tile(x, y, stage, COLL_LEFT);

        if (wall.distance > 0) return;

        player->xSpeed -= FIXED8(wall.distance, 0);
        player->groundSpeed = 0;
    }

    sprite_set_animation(player->sprite, &player->anim[ANIM_PUSH]);
    animDuration = mf_max(0, 8 - mf_abs(fixed8_to_int(player->groundSpeed))) * 4;

    player->isPushing = TRUE;
}


INLINE void airborne_move_right(Player *player)
{
    if (player->xSpeed < player->maxSpd) {
        player->xSpeed += player->airAccel;
        if (player->xSpeed >= player->maxSpd) {
            player->xSpeed = player->maxSpd;
        }
    }
}

INLINE void airborne_move_left(Player *player)
{
    if (player->xSpeed > -player->maxSpd) {
        player->xSpeed -= player->airAccel;
        if (player->xSpeed <= -player->maxSpd) {
            player->xSpeed = -player->maxSpd;
        }
    }
}

INLINE void airborne_airdrag(Player *player)
{
    if (player->ySpeed < 0 && player->ySpeed > -FIXED8(4, 0)) {
        player->xSpeed -= ((player->xSpeed / FIXED8(0, 32)) / FIXED8(256, 0));
    }
}

INLINE void airborne_gravity(Player *player)
{
    player->ySpeed += gravity;
    if (player->ySpeed > player->maxVerticSpd)
        player->ySpeed = player->maxVerticSpd;
}

static void airborne_camera_follow(Player *player, Camera *camera)
{
    fixed8 rightBorder  = camera->xPos + camRightBorder;
    fixed8 leftBorder   = camera->xPos + camLeftBorder;
    fixed8 topBorder    = camera->yPos + camTopBorder;
    fixed8 bottomBorder = camera->yPos + camBottomBorder;

    fixed8 targetX = player->xPos;
    fixed8 targetY = player->yPos;

    camera->xSpeed = 0;
    camera->ySpeed = 0;

    if (targetX > rightBorder)
        camera->xSpeed += targetX - rightBorder;
    else if (targetX < leftBorder)
        camera->xSpeed -= leftBorder - targetX;
    
    if (targetY > bottomBorder)
        camera->ySpeed += targetY - bottomBorder;
    else if (targetY < topBorder)
        camera->ySpeed -= topBorder - targetY;
}

INLINE void airborne_right_wall_collision(Player *player, const Stage *stage)
{
    int x = fixed8_to_int(player->xPos) + player->pushRadius;
    int y = fixed8_to_int(player->yPos);

    SolidTile rWall = collision_find_horizontal_tile(x, y, stage, COLL_RIGHT);

    if (rWall.distance >= 0) return;

    player->xPos += FIXED8(rWall.distance, 0);
    player->xSpeed = 0;
}
INLINE void airborne_left_wall_collision(Player *player, const Stage *stage)
{
    int x = fixed8_to_int(player->xPos) - player->pushRadius;
    int y = fixed8_to_int(player->yPos);

    SolidTile lWall = collision_find_horizontal_tile(x, y, stage, COLL_LEFT);

    if (lWall.distance >= 0) return;

    player->xPos -= FIXED8(lWall.distance, 0);
    player->xSpeed = 0;
}
INLINE void airborne_ground_collision(Player *player, const Stage *stage)
{
    int x = fixed8_to_int(player->xPos);
    int y = fixed8_to_int(player->yPos) + player->height;

    SolidTile solidTileA = collision_find_vertical_tile(x - player->width, y, stage, COLL_DOWN);
    SolidTile solidTileB = collision_find_vertical_tile(x + player->width, y, stage, COLL_DOWN);

    SolidTile choosenTile = solidTileA.distance <= solidTileB.distance ? solidTileA : solidTileB;

    if (choosenTile.distance >= 0) return;

    flagged_tile_check(player, &choosenTile);
    
    player->yPos += FIXED8(choosenTile.distance, 0);
    player->groundSpeed = player->xSpeed;

    player->state = STATE_NORMAL;
}
INLINE void airborne_ceiling_collision(Player *player, const Stage *stage)
{
    int x = fixed8_to_int(player->xPos);
    int y = fixed8_to_int(player->yPos) - player->height;

    SolidTile solidTileA = collision_find_vertical_tile(x - player->width, y, stage, COLL_UP);
    SolidTile solidTileB = collision_find_vertical_tile(x + player->width, y, stage, COLL_UP);

    SolidTile choosenTile = solidTileA.distance <= solidTileB.distance ? solidTileA : solidTileB;

    if (choosenTile.distance >= 0) return;

    player->yPos -= FIXED8(choosenTile.distance, 0);
    player->ySpeed = 0;
}

static void airborne_collision(Player *player, const Stage *stage)
{
    //get player move direction
    u8 angle = angle_direction(fixed8_to_int(player->xSpeed), fixed8_to_int(player->ySpeed));
    Direction dir;
    if      (angle <= 31 || angle >= 224) dir = RIGHT;
    else if (angle >= 32 && angle <= 95) dir = DOWN;
    else if (angle >= 96 && angle <= 159) dir = LEFT;
    else dir = UP;

    switch (dir)
    {
        case RIGHT:

            airborne_right_wall_collision(player, stage);

            airborne_ground_collision(player, stage);

            airborne_ceiling_collision(player, stage);

        break;

        case DOWN:

            //floor collision check
            {
                int x = fixed8_to_int(player->xPos);
                int y = fixed8_to_int(player->yPos) + player->height;
    
                SolidTile solidTileA = collision_find_vertical_tile(x - player->width, y, stage, COLL_DOWN);
                SolidTile solidTileB = collision_find_vertical_tile(x + player->width, y, stage, COLL_DOWN);
    
                SolidTile choosenTile = solidTileA.distance <= solidTileB.distance ? solidTileA : solidTileB;
    
                if (choosenTile.distance < 0 &&
                    solidTileA.distance >= -(fixed8_to_int(player->ySpeed) + 8) &&
                    solidTileB.distance >= -(fixed8_to_int(player->ySpeed) + 8))
                {
        
                    player->yPos += FIXED8(choosenTile.distance, 0);
                    player->groundAngle = choosenTile.angle;
        
                    flagged_tile_check(player, &choosenTile);
                    
                    //decide ground speed based on the angle we landed
                    //flat
                    if (player->groundAngle <= 15 || player->groundAngle >= 240) {
                        player->groundSpeed = player->xSpeed;
                    }
                    //slope
                    else if (player->groundAngle <= 31 || player->groundAngle >= 224) {
                        player->groundSpeed = (player->ySpeed / 2) * -mf_sign(-angle_sin(player->groundAngle));
                    }
                    //steep
                    else {
                        player->groundSpeed = player->ySpeed * -mf_sign(-angle_sin(player->groundAngle));
                    }
    
                    player->state = STATE_NORMAL;
                }
            }

            //walls collision check
            airborne_right_wall_collision(player, stage);
            airborne_left_wall_collision(player, stage);

        break;

        case LEFT:

            airborne_left_wall_collision(player, stage);

            airborne_ground_collision(player, stage);

            airborne_ceiling_collision(player, stage);

        break;

        case UP:

            //ceiling collision check
            {
                int x = fixed8_to_int(player->xPos);
                int y = fixed8_to_int(player->yPos) - player->height;
    
                SolidTile solidTileA = collision_find_vertical_tile(x - player->width, y, stage, COLL_UP);
                SolidTile solidTileB = collision_find_vertical_tile(x + player->width, y, stage, COLL_UP);
    
                SolidTile choosenTile = solidTileA.distance <= solidTileB.distance ? solidTileA : solidTileB;
    
                if (choosenTile.distance < 0)
                {
                    player->yPos -= FIXED8(choosenTile.distance, 0);
                    
                    //decide ground speed based on the angle we landed
                    //flat
                    if (choosenTile.angle >= 66 && choosenTile.angle <= 191) {
                        player->ySpeed = 0;
                    }
                    //steep
                    else {
                        player->groundSpeed = player->ySpeed * -mf_sign(-angle_sin(player->groundAngle));
    
                        player->groundAngle = choosenTile.angle;
    
                        flagged_tile_check(player, &choosenTile);
    
                        player->state = STATE_NORMAL;
                    }
                }
            }

            //walls collision check
            airborne_right_wall_collision(player, stage);
            airborne_left_wall_collision(player, stage);

        break;
    }
}

static void debug_mode_move(Player *player)
{
    if (key_is_down(KEY_UP))
        player->ySpeed -= debugModeAcc;
    if (key_is_down(KEY_DOWN))
        player->ySpeed += debugModeAcc;
    if (key_is_down(KEY_LEFT))
        player->xSpeed -= debugModeAcc;
    if (key_is_down(KEY_RIGHT))
        player->xSpeed += debugModeAcc;
    if (!key_is_down(KEY_UP | KEY_DOWN | KEY_LEFT | KEY_RIGHT)){
        player->xSpeed -= mf_min(mf_abs(player->xSpeed), debugModeAcc) * mf_sign(player->xSpeed);
        player->ySpeed -= mf_min(mf_abs(player->ySpeed), debugModeAcc) * mf_sign(player->ySpeed);
    }

    player->xPos += player->xSpeed;
    player->yPos += player->ySpeed;
}

INLINE void flagged_tile_check(Player *player, const SolidTile *choosenTile)
{
    if (choosenTile->angle != FLAGGED_ANGLE) return;

    player->groundAngle = ((player->groundAngle + 32) / 64) * 64;
}

INLINE void bounds_collision(Player *player, const Camera *camera)
{
    fixed8 x, y, xx, yy;

    x = player->xPos - FIXED8(player->pushRadius, 0);
    y = player->yPos - FIXED8(player->height, 0);
    xx = player->xPos + FIXED8(player->pushRadius, 0);
    yy = player->yPos + FIXED8(player->height, 0);


    if (x < camera->minHorizBorder) {
        player->xPos += camera->minHorizBorder - x;
        player->xSpeed /= 2;
    }
    else if (xx > camera->maxHorizBorder) {
        player->xPos -= xx - camera->maxHorizBorder;
        player->xSpeed /= 2;
    }

    if (y < camera->minVertBorder) {
        player->yPos += camera->minVertBorder - y;
        player->ySpeed /= 2;
    }
    else if (yy > camera->maxVertBorder) {
        player->yPos -= yy - camera->maxVertBorder;
        player->ySpeed /= 2;
    }
}

INLINE void update_speed(Player *player)
{
    player->xSpeed = (player->groundSpeed * angle_cos(player->groundAngle)) >> 8;
    player->ySpeed = (player->groundSpeed * -angle_sin(player->groundAngle)) >> 8;
}

INLINE void update_position(Player *player)
{
    player->xPos += player->xSpeed;
    player->yPos += player->ySpeed;
}
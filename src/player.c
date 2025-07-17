#include "gba.h"
#include "player.h"
#include "collision.h"
#include <stdlib.h>

static playerCharData charData;

static int animDuration;

static fixed8 camLeftBorder     = FIXED8(113, 0);
static fixed8 camRightBorder    = FIXED8(125, 0);
static fixed8 camTopBorder      = FIXED8(57, 0);
static fixed8 camVerticalPoint  = FIXED8(79, 0);
static fixed8 camBottomBorder   = FIXED8(101, 0);

static fixed8 gravity = FIXED8(0, 53);

static fixed8 slopeFactorNormal   = FIXED8(0, 52);
static fixed8 slopeFactorRollup   = FIXED8(0, 20);
static fixed8 slopeFactorRolldown = FIXED8(0, 80);

static fixed8 debugModeAcc = FIXED8(0, 20);


/*==========PLAYER VARIABLES===========================*/
//TODO: Set variables specific to different characters
static int playerWidth;
static int playerHeight;

static fixed8 playerAcc = FIXED8(0, 10);
static fixed8 playerDecel = FIXED8(0, 128);
static fixed8 playerFric = FIXED8(0, 10);
static fixed8 playerAirAcc = FIXED8(0, 24);

static fixed8 playerMaxSpeed = FIXED8(5, 0);
static fixed8 playerMaxVerticalSpeed = FIXED8(16, 0);

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

INLINE void bounds_collision(Player *player, const Stage *stage);
INLINE void update_speed(Player *player);
INLINE void update_position(Player *player);


/*=============FUNCTIONS=========================*/

Player *player_create(fixed8 xPos, fixed8 yPos, playerState state, playerCharacter character, struct SpriteListNode **sprNode)
{
    Player *player;

    player = (Player *)calloc(1, sizeof(Player));

    player->xPos = xPos;
    player->yPos = yPos;
    player->state = state;

    charData = playerCharTable[character];

    playerWidth = charData.width;
    playerHeight = charData.height;

    //sprite load
    player->sprite = sprite_create(sprNode, 0, 0, 0, 0, 0, 0, 1, (ObjShape*)0);
    
    palette_load(charData.palData, charData.palDataLenght, PAL_OAM_INDEX);

    sprite_set_animation(player->sprite, &charData.playerAnim[ANIM_IDLE]);

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

                if (player->groundSpeed < 0)
                    normal_decelerate_right(player);
                
                normal_move_right(player);

            }
            if (key_is_down(KEY_LEFT)) {

                if (player->groundSpeed > 0)
                    normal_decelerate_left(player);
                
                normal_move_left(player);

            }
            if (!key_is_down(KEY_RIGHT | KEY_LEFT))
                normal_friction(player);

            update_speed(player);
            
            normal_walls_collision(player, stage);

            update_position(player);

            normal_ground_collision(player, stage);

            normal_camera_follow(player, camera);
        break;

        case STATE_ROLLING:

        break;

        case STATE_AIRBORNE:

            if (key_is_down(KEY_RIGHT))
                airborne_move_right(player);

            if (key_is_down(KEY_LEFT))
                airborne_move_left(player);
            
            airborne_airdrag(player);

            airborne_camera_follow(player, camera);

            update_position(player);
            
            airborne_gravity(player);

            airborne_collision(player, stage);
        break;

        case STATE_DEBUG:
            
            debug_mode_move(player);
            
            normal_camera_follow(player, camera);
        break;
    }

    bounds_collision(player, stage);

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
    
        if (mf_abs(player->groundSpeed) >= playerMaxSpeed) {
            sprite_set_animation(player->sprite, &charData.playerAnim[ANIM_RUN]);
        } 
        else if (player->groundSpeed != 0) {
            sprite_set_animation(player->sprite, &charData.playerAnim[ANIM_WALK]);
        }
        else {
            sprite_set_animation(player->sprite, &charData.playerAnim[ANIM_IDLE]);
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
    if (player->groundSpeed < playerMaxSpeed) {
        player->groundSpeed += playerAcc;
        if (player->groundSpeed >= playerMaxSpeed) {
            player->groundSpeed = playerMaxSpeed;
        }
    }
}

INLINE void normal_decelerate_right(Player *player)
{
    player->groundSpeed += playerDecel;
    if (player->groundSpeed >= 0)
        player->groundSpeed = FIXED8(0, 128);
}

INLINE void normal_move_left(Player *player)
{
    if (player->groundSpeed > -playerMaxSpeed) {
        player->groundSpeed -= playerAcc;
        if (player->groundSpeed <= -playerMaxSpeed) {
            player->groundSpeed = -playerMaxSpeed;
        }
    }
}

INLINE void normal_decelerate_left(Player *player)
{
    player->groundSpeed -= playerDecel;
    if (player->groundSpeed <= 0)
        player->groundSpeed = -FIXED8(0, 128);
}

INLINE void normal_friction(Player *player)
{
    player->groundSpeed -= mf_min(mf_abs(player->groundSpeed), playerFric) * mf_sign(player->groundSpeed);
}

static void normal_camera_follow(Player *player, Camera *camera)
{
    fixed8 rightBorder   = camera->xPos + camRightBorder;
    fixed8 leftBorder    = camera->xPos + camLeftBorder;
    fixed8 verticalPoint = camera->yPos + camVerticalPoint;

    fixed8 playerTargetX = player->xPos;
    fixed8 playerTargetY = player->yPos;

    camera->xSpeed = 0;
    camera->ySpeed = 0;

    if (playerTargetX > rightBorder)
        camera->xSpeed += playerTargetX - rightBorder;
    else if (playerTargetX < leftBorder)
        camera->xSpeed -= leftBorder - playerTargetX;
    if (playerTargetY != verticalPoint)
        camera->ySpeed += playerTargetY - verticalPoint;
}

static void normal_ground_collision(Player *player, const Stage *stage)
{
    int x = fixed8_to_int(player->xPos);
    int y = fixed8_to_int(player->yPos) + playerHeight;

    SolidTile solidTileA = collision_find_vertical_tile(x - playerWidth, y, stage, COLL_DOWN);
    SolidTile solidTileB = collision_find_vertical_tile(x + playerWidth, y, stage, COLL_DOWN);

    SolidTile choosenTile = solidTileA.distance <= solidTileB.distance ? solidTileA : solidTileB;

    if (choosenTile.distance > mf_min(mf_abs(fixed8_to_int(player->xSpeed)) + 4, 14)) {
        //player->state = STATE_AIRBORNE;
        return;
    }
    player->yPos += FIXED8(choosenTile.distance, 0);

    player->groundAngle = choosenTile.angle;

    if (choosenTile.angle == FLAGGED_ANGLE) {
        player->groundAngle = ((player->groundAngle + 32) / 64) * 64;
    }
}

static void normal_walls_collision(Player *player, const Stage *stage)
{
    if (player->groundSpeed == 0) return;

    int pushRadius = playerWidth + 1;
    int yoffset = 8 * (player->groundAngle == 0);

    //check for right wall collision
    if (player->groundSpeed > 0)
    {
        int x = fixed8_to_int(player->xPos + player->xSpeed) + pushRadius;
        int y = fixed8_to_int(player->yPos + player->ySpeed) + yoffset;

        SolidTile wall = collision_find_horizontal_tile(x, y, stage, COLL_RIGHT);

        if (wall.distance > 0) return;

        player->xSpeed += FIXED8(wall.distance, 0);
        player->groundSpeed = 0;
    }
    else if (player->groundSpeed < 0)
    {
        int x = fixed8_to_int(player->xPos + player->xSpeed) - pushRadius;
        int y = fixed8_to_int(player->yPos + player->ySpeed) + yoffset;

        SolidTile wall = collision_find_horizontal_tile(x, y, stage, COLL_LEFT);

        if (wall.distance > 0) return;

        player->xSpeed -= FIXED8(wall.distance, 0);
        player->groundSpeed = 0;
    }

    sprite_set_animation(player->sprite, &charData.playerAnim[ANIM_PUSH]);
    animDuration = mf_max(0, 8 - mf_abs(fixed8_to_int(player->groundSpeed))) * 4;

    player->isPushing = TRUE;
}



INLINE void airborne_move_right(Player *player)
{
    if (player->xSpeed < playerMaxSpeed) {
        player->xSpeed += playerAirAcc;
        if (player->xSpeed >= playerMaxSpeed) {
            player->xSpeed = playerMaxSpeed;
        }
    }
}

INLINE void airborne_move_left(Player *player)
{
    if (player->xSpeed > -playerMaxSpeed) {
        player->xSpeed -= playerAirAcc;
        if (player->xSpeed <= -playerMaxSpeed) {
            player->xSpeed = -playerMaxSpeed;
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
    if (player->ySpeed > playerMaxVerticalSpeed)
        player->ySpeed = playerMaxVerticalSpeed;
}

static void airborne_camera_follow(Player *player, Camera *camera)
{
    fixed8 rightBorder  = camera->xPos + camRightBorder;
    fixed8 leftBorder   = camera->xPos + camLeftBorder;
    fixed8 topBorder    = camera->yPos + camTopBorder;
    fixed8 bottomBorder = camera->yPos + camBottomBorder;

    fixed8 playerTargetX = player->xPos + player->xSpeed;
    fixed8 playerTargetY = player->yPos + player->ySpeed;

    camera->xSpeed = 0;
    camera->ySpeed = 0;

    if (playerTargetX > rightBorder)
        camera->xSpeed += playerTargetX - rightBorder;
    else if (playerTargetX < leftBorder)
        camera->xSpeed -= leftBorder - playerTargetX;
    
    if (playerTargetY > bottomBorder)
        camera->ySpeed += playerTargetY - bottomBorder;
    else if (playerTargetY < topBorder)
        camera->ySpeed -= topBorder - playerTargetY;
}

static void airborne_collision(Player *player, const Stage *stage)
{

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

INLINE void bounds_collision(Player *player, const Stage *stage)
{
    if (player->xPos - FIXED8(playerWidth, 0) < 0) {
        player->xPos += 0 - (player->xPos - FIXED8(playerWidth, 0));
        player->xSpeed /= 2;
    }
    else if (player->xPos + FIXED8(playerWidth, 0) > FIXED8(stage->mapWidth, 0)) {
        player->xPos -= (player->xPos + FIXED8(playerWidth, 0)) - FIXED8(stage->mapWidth, 0);
        player->xSpeed /= 2;
    }

    if (player->yPos - FIXED8(playerHeight, 0) < 0) {
        player->yPos += 0 - (player->yPos - FIXED8(playerHeight, 0));
        player->ySpeed /= 2;
    }
    else if (player->yPos + FIXED8(playerHeight, 0) > FIXED8(stage->mapHeight, 0)) {
        player->yPos -= (player->yPos + FIXED8(playerHeight, 0)) - FIXED8(stage->mapHeight, 0);
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
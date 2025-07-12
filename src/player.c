#include "gba.h"
#include <stdlib.h>
#include "player.h"

static fixed8 camLeftBorder     = FIXED8(113, 0);
static fixed8 camRightBorder    = FIXED8(125, 0);
static fixed8 camTopBorder      = FIXED8(57, 0);
static fixed8 camVerticalPoint  = FIXED8(79, 0);
static fixed8 camBottomBorder   = FIXED8(101, 0);

static int animDuration;

static playerCharData charData;

static fixed8 gravity = FIXED8(0, 53);

/*==========PLAYER VARIABLES===========================*/
//TODO: Set variables specific to different characters
static int playerWidth;
static int playerHeight;

static fixed8 playerAcc = FIXED8(0, 14);
static fixed8 playerDecel = FIXED8(0, 128);
static fixed8 playerFric = FIXED8(0, 14);
static fixed8 playerAirAcc = FIXED8(0, 24);

static fixed8 playerMaxSpeed = FIXED8(6, 0);
static fixed8 playerMaxVerticalSpeed = FIXED8(16, 0);

/*==========PRIVATE FUNCTIONS===================*/
INLINE void normal_move_right(Player *player);
INLINE void normal_decelerate_right(Player *player);
INLINE void normal_move_left(Player *player);
INLINE void normal_decelerate_left(Player *player);
INLINE void normal_friction(Player *player);
void        normal_camera_follow(Player *player, Camera *camera);

INLINE void airborne_move_right(Player *player);
INLINE void airborne_move_left(Player *player);
INLINE void airborne_airdrag(Player *player);
INLINE void airborne_gravity(Player *player);
void        airborne_camera_follow(Player *player, Camera *camera);

INLINE void bounds_camera_collision(Player *player, Camera *camera);
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

    return player;
}

void player_routine(Player *player, Camera *camera)
{
    switch (player->state)
    {
        case STATE_NORMAL:

            if (key_is_down(KEY_RIGHT)) {

                if (player->xSpeed < 0)
                    normal_decelerate_right(player);
                
                normal_move_right(player);

            }
            if (key_is_down(KEY_LEFT)) {

                if (player->xSpeed > 0)
                    normal_decelerate_left(player);
                
                normal_move_left(player);

            }
            if (!key_is_down(KEY_RIGHT | KEY_LEFT))
                normal_friction(player);

            normal_camera_follow(player, camera);

            update_position(player);

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

        break;
    }

    bounds_camera_collision(player, camera);

}

void player_render(Player *player, Camera *camera)
{
    if (key_is_down(KEY_RIGHT))
        player->sprite->hFlip = FALSE;
    if (key_is_down(KEY_LEFT))
        player->sprite->hFlip = TRUE;

    player->sprite->xPos = fixed8_to_int(player->xPos - camera->xPos);
    player->sprite->yPos = fixed8_to_int(player->yPos - camera->yPos);

    animDuration = mf_max(0, 8 - mf_abs(fixed8_to_int(player->xSpeed)));

    //TEMP
    //TODO: Set animations specific to player state
    if (mf_abs(player->xSpeed) >= FIXED8(6, 0)) {
        sprite_set_animation(player->sprite, &charData.playerAnim[ANIM_RUN]);
    } 
    else if (mf_abs(player->xSpeed) > 0) {
        sprite_set_animation(player->sprite, &charData.playerAnim[ANIM_WALK]);
    }
    else {
        sprite_set_animation(player->sprite, &charData.playerAnim[ANIM_IDLE]);
        animDuration = 0;
    }

    sprite_render_animation(player->sprite, animDuration);
}

void player_destroy(Player *player)
{
    free(player);
    player = NULL;
}

/*=================PRIVATE FUNCTIONS==========================*/

INLINE void normal_move_right(Player *player)
{
    if (player->xSpeed < playerMaxSpeed) {
        player->xSpeed += playerAcc;
        if (player->xSpeed >= playerMaxSpeed) {
            player->xSpeed = playerMaxSpeed;
        }
    }
}

INLINE void normal_decelerate_right(Player *player)
{
    player->xSpeed += playerDecel;
    if (player->xSpeed >= 0)
        player->xSpeed = FIXED8(0, 128);
}

INLINE void normal_move_left(Player *player)
{
    if (player->xSpeed > -playerMaxSpeed) {
        player->xSpeed -= playerAcc;
        if (player->xSpeed <= -playerMaxSpeed) {
            player->xSpeed = -playerMaxSpeed;
        }
    }
}

INLINE void normal_decelerate_left(Player *player)
{
    player->xSpeed -= playerDecel;
    if (player->xSpeed <= 0)
        player->xSpeed = -FIXED8(0, 128);
}

INLINE void normal_friction(Player *player)
{
    player->xSpeed -= mf_min(mf_abs(player->xSpeed), playerFric) * mf_sign(player->xSpeed);
}

void normal_camera_follow(Player *player, Camera *camera)
{
    fixed8 rightBorder   = camera->xPos + camRightBorder;
    fixed8 leftBorder    = camera->xPos + camLeftBorder;
    fixed8 verticalPoint = camera->yPos + camVerticalPoint;

    fixed8 playerTargetX = player->xPos + player->xSpeed;
    fixed8 playerTargetY = player->yPos + player->ySpeed;

    camera->xSpeed = 0;
    camera->ySpeed = 0;

    if (playerTargetX > rightBorder)
        camera->xSpeed += playerTargetX - rightBorder;
    else if (playerTargetX < leftBorder)
        camera->xSpeed -= leftBorder - playerTargetX;
    if (playerTargetY != verticalPoint)
        camera->ySpeed += playerTargetY - verticalPoint;
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

void airborne_camera_follow(Player *player, Camera *camera)
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

INLINE void bounds_camera_collision(Player *player, Camera *camera)
{
    if (player->xPos - FIXED8(playerWidth, 0) < camera->minHorizBorder) {
        player->xPos += camera->minHorizBorder - (player->xPos - FIXED8(playerWidth, 0));
        player->xSpeed /= 2;
    }
    else if (player->xPos + FIXED8(playerWidth, 0) > camera->maxHorizBorder) {
        player->xPos -= (player->xPos + FIXED8(playerWidth, 0)) - camera->maxHorizBorder;
        player->xSpeed /= 2;
    }
}

INLINE void update_position(Player *player)
{
    player->xPos += player->xSpeed;
    player->yPos += player->ySpeed;
}
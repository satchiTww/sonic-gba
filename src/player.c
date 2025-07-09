#include "gba.h"
#include <stdlib.h>
#include "player.h"

static int camLeftBorder     = 113;
static int camRightBorder    = 125;
static int camVerticalPoint  = 68;
static int camTopBorder      = 46;
static int camBottomBorder   = 90;

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
INLINE void player_decelerate_right(Player *player);
INLINE void player_normal_move_right(Player *player);
INLINE void player_decelerate_left(Player *player);
INLINE void player_normal_move_left(Player *player);
INLINE void player_normal_friction(Player *player);
INLINE void player_airborne_move_right(Player *player);
INLINE void player_airborne_move_left(Player *player);
INLINE void player_airborne_airdrag(Player *player);
INLINE void player_airborne_gravity(Player *player);
INLINE void player_bounds_collision(Player *player);
INLINE void player_update_position(Player *player);

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
                    player_decelerate_right(player);
                
                player_normal_move_right(player);

            }
            if (key_is_down(KEY_LEFT)) {

                if (player->xSpeed > 0)
                    player_decelerate_left(player);
                
                player_normal_move_left(player);

            }
            if (!key_is_down(KEY_RIGHT | KEY_LEFT))
                player_normal_friction(player);

            camera_follow_target(
                camera,
                fixed8_to_int(player->xPos + player->xSpeed),
                fixed8_to_int(player->yPos + player->ySpeed),
                camLeftBorder,
                camRightBorder,
                camVerticalPoint,
                camVerticalPoint
            );

            player_update_position(player);

        break;

        case STATE_ROLLING:

        break;

        case STATE_AIRBORNE:

            if (key_is_down(KEY_RIGHT))
                player_airborne_move_right(player);

            if (key_is_down(KEY_LEFT))
                player_airborne_move_left(player);
            
            player_airborne_airdrag(player);

            camera_follow_target(
                camera,
                fixed8_to_int(player->xPos + player->xSpeed),
                fixed8_to_int(player->yPos + player->ySpeed),
                camLeftBorder,
                camRightBorder,
                camTopBorder,
                camBottomBorder
            );

            player_update_position(player);
            
            player_airborne_gravity(player);

        break;
    }

    player_bounds_collision(player);

}

void player_render(Player *player, Camera *camera)
{
    if (key_is_down(KEY_RIGHT))
        player->sprite->hFlip = FALSE;
    if (key_is_down(KEY_LEFT))
        player->sprite->hFlip = TRUE;

    player->sprite->xPos = fixed8_to_int(player->xPos) - camera->xPos;
    player->sprite->yPos = fixed8_to_int(player->yPos) - camera->yPos;

    animDuration = mf_max(0, 8 - mf_abs(fixed8_to_int(player->xSpeed)));

    if (mf_abs(player->xSpeed) >= FIXED8(6, 0)) {
        sprite_set_animation(player->sprite, &charData.playerAnim[ANIM_RUN]);
    } 
    else if (mf_abs(player->xSpeed) > 0) {
        sprite_set_animation(player->sprite, &charData.playerAnim[ANIM_WALK]);
    }
    else {
        sprite_set_animation(player->sprite, &charData.playerAnim[ANIM_IDLE]);
    }

    sprite_render_animation(player->sprite, animDuration);
}

void player_destroy(Player *player)
{
    free(player);
    player = NULL;
}

/*=================PRIVATE FUNCTIONS==========================*/

INLINE void player_decelerate_right(Player *player)
{
    player->xSpeed += playerDecel;
    if (player->xSpeed >= 0)
        player->xSpeed = FIXED8(0, 128);
}

INLINE void player_normal_move_right(Player *player)
{
    if (player->xSpeed < playerMaxSpeed) {
        player->xSpeed += playerAcc;
        if (player->xSpeed >= playerMaxSpeed) {
            player->xSpeed = playerMaxSpeed;
        }
    }
}

INLINE void player_decelerate_left(Player *player)
{
    player->xSpeed -= playerDecel;
    if (player->xSpeed <= 0)
        player->xSpeed = -FIXED8(0, 128);
}

INLINE void player_normal_move_left(Player *player)
{
    if (player->xSpeed > -playerMaxSpeed) {
        player->xSpeed -= playerAcc;
        if (player->xSpeed <= -playerMaxSpeed) {
            player->xSpeed = -playerMaxSpeed;
        }
    }
}

INLINE void player_normal_friction(Player *player)
{
    player->xSpeed -= mf_min(mf_abs(player->xSpeed), playerFric) * mf_sign(player->xSpeed);
}

INLINE void player_airborne_move_right(Player *player)
{
    if (player->xSpeed < playerMaxSpeed) {
        player->xSpeed += playerAirAcc;
        if (player->xSpeed >= playerMaxSpeed) {
            player->xSpeed = playerMaxSpeed;
        }
    }
}

INLINE void player_airborne_move_left(Player *player)
{
    if (player->xSpeed > -playerMaxSpeed) {
        player->xSpeed -= playerAirAcc;
        if (player->xSpeed <= -playerMaxSpeed) {
            player->xSpeed = -playerMaxSpeed;
        }
    }
}

INLINE void player_airborne_airdrag(Player *player)
{
    if (player->ySpeed < 0 && player->ySpeed > -FIXED8(4, 0)) {
        player->xSpeed -= ((player->xSpeed / FIXED8(0, 32)) / FIXED8(256, 0));
    }
}

INLINE void player_airborne_gravity(Player *player)
{
    player->ySpeed += gravity;
    if (player->ySpeed > playerMaxVerticalSpeed)
        player->ySpeed = playerMaxVerticalSpeed;
}

INLINE void player_bounds_collision(Player *player)
{
    if (fixed8_to_int(player->xPos + player->xSpeed) - playerWidth < 0) {
        player->xPos = FIXED8(playerWidth, 0);
        player->xSpeed = 0;
    }
}

INLINE void player_update_position(Player *player)
{
    player->xPos += player->xSpeed;
    player->yPos += player->ySpeed;
}
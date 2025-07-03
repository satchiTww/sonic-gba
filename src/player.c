#include "gba.h"
#include "player.h"
#include <stdlib.h>

static fixed8 gravity = FIXED8(0, 53);

/*==========PLAYER VARIABLES===========================*/
//TODO: Set variables specific to different characters
static int playerWidth = 10;
static int playerHeight = 19;

static fixed8 playerAcc = FIXED8(0, 14);
static fixed8 playerFric = FIXED8(0, 14);
static fixed8 playerAirAcc = FIXED8(0, 24);

static fixed8 playerMaxSpeed = FIXED8(6, 0);
static fixed8 playerMaxVerticalSpeed = FIXED8(16, 0);

/*==========PRIVATE FUNCTIONS===================*/
INLINE void player_normal_move_right(Player *player);
INLINE void player_normal_move_left(Player *player);
INLINE void player_normal_friction(Player *player);
INLINE void player_airborne_move_right(Player *player);
INLINE void player_airborne_move_left(Player *player);
INLINE void player_airborne_airdrag(Player *player);
INLINE void player_airborne_gravity(Player *player);
INLINE void player_bounds_collision(Player *player);
INLINE void player_update_position(Player *player);

/*=============FUNCTIONS=========================*/

Player *player_create(fixed8 xPos, fixed8 yPos, playerState state)
{
    Player *player;

    player = (Player *)calloc(1, sizeof(Player));

    player->xPos = xPos;
    player->yPos = yPos;
    player->state = state;

    return player;
}

void player_routine(Player *player)
{
    switch (player->state)
    {
    case NORMAL:
        if (key_is_down(KEY_RIGHT))
            player_normal_move_right(player);
        if (key_is_down(KEY_LEFT))
            player_normal_move_left(player);
        if (!key_is_down(KEY_RIGHT | KEY_LEFT))
            player_normal_friction(player);
        
        player_update_position(player);
        break;
    case ROLLING:
        break;
    case AIRBORNE:
        if (key_is_down(KEY_RIGHT))
            player_airborne_move_right(player);
        if (key_is_down(KEY_LEFT))
            player_airborne_move_left(player);
        
        player_airborne_airdrag(player);

        player_update_position(player);
        
        //player_airborne_gravity(player);
        break;
    }
    player_bounds_collision(player);
}

void player_destroy(Player *player)
{
    free(player);
    player = NULL;
}

/*=================PRIVATE FUNCTIONS==========================*/

INLINE void player_normal_move_right(Player *player)
{
    if (player->xSpeed < playerMaxSpeed) {
        player->xSpeed += playerAcc;
        if (player->xSpeed >= playerMaxSpeed) {
            player->xSpeed = playerMaxSpeed;
        }
    }
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
    if (player->xSpeed > 0)
        player->xSpeed -= playerFric;
    if (player->xSpeed < 0)
        player->xSpeed += playerFric;
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
#ifndef PLAYER_H
#define PLAYER_H

#include "gba_typedefs.h"

typedef enum {
    NORMAL,
    ROLLING,
    AIRBORNE
} playerState;

typedef struct {
    fixed8 xPos, yPos;
    fixed8 xSpeed, ySpeed;
    fixed8 groundSpeed;
    fixed8 groundAngle;
    playerState state;
} Player;

Player *player_create(fixed8 xPos, fixed8 yPos, playerState state);
void player_routine(Player *player);
void player_destroy(Player *player);

#endif
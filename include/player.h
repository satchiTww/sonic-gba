#ifndef PLAYER_H
#define PLAYER_H

#include "gba_typedefs.h"
#include "math_func.h"
#include "camera.h"
#include "sprite.h"

typedef enum {
    STATE_NORMAL,
    STATE_ROLLING,
    STATE_AIRBORNE
} playerState;

typedef struct {
    fixed8 xPos, yPos;
    fixed8 xSpeed, ySpeed;
    fixed8 groundSpeed;
    fixed8 groundAngle;
    playerState state;
    Sprite *sprite;
} Player;

typedef enum {
    CHAR_SONIC,
    CHAR_TAILS,
    CHAR_KNUCKLES,
    CHAR_MIKU,
    CHAR_TETO,
    CHAR_NERU,
    NUM_OF_PLAYER_CHARS,
} playerCharacter;

typedef enum {
    ANIM_IDLE,
    ANIM_WALK,
    ANIM_RUN,
    NUM_OF_PLAYER_ANIM,
} playerAnimations;

typedef struct {
    const u16 *palData;
    int palDataLenght;
    AnimatedSprite *playerAnim;
    int width;
    int height;
} playerCharData;

extern playerCharData playerCharTable[NUM_OF_PLAYER_CHARS];

Player *player_create(fixed8 xPos, fixed8 yPos, playerState state, playerCharacter character, struct SpriteListNode **sprNode);
void player_routine(Player *player, Camera *camera);
void player_render(Player *player, Camera *camera);
void player_destroy(Player *player);

#endif
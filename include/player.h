#ifndef PLAYER_H
#define PLAYER_H

#include "gba_typedefs.h"
#include "math_func.h"
#include "camera.h"
#include "sprite.h"
#include "stage.h"

typedef enum {
    STATE_NORMAL,
    STATE_ROLLING,
    STATE_AIRBORNE,
    STATE_DEBUG
} playerState;

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
    ANIM_PUSH,
    ANIM_ROLL,
    NUM_OF_PLAYER_ANIM,
} playerAnimations;

typedef struct {
    const u16 *palData;
    u32 palDataLenght;
    AnimatedSprite *playerAnim;
    u32 width;
    u32 height;
} playerCharData;

typedef struct {
    fixed8 xPos, yPos;
    fixed8 xSpeed, ySpeed;
    fixed8 groundSpeed;
    u8 groundAngle;

    playerState state;

    playerCharData *charData;

    u32 width;
    u32 height;
    u32 pushRadius;

    fixed8 accel;
    fixed8 decel;
    fixed8 fric;
    fixed8 airAccel;
    fixed8 maxSpd;
    fixed8 maxVerticSpd;
    fixed8 jumpForce;

    //anim flags
    u32 isJumping:1;
    u32 isPushing:1;
    u32 isBall:1;
    
    Sprite *sprite;
    AnimatedSprite *anim;

} Player;

Player *player_create(fixed8 xPos, fixed8 yPos, playerState state, playerCharacter character, struct SpriteListNode **sprNode);
void player_routine(Player *player, Camera *camera, const Stage *stage);
void player_animate(Player *player, Camera *camera);
void player_destroy(Player *player);

#endif
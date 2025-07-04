#ifndef ANIMATION_DATA_H
#define ANIMATION_DATA_H

#include "animation.h"

//TETO
typedef enum {
    ANIM_TETO_IDLE,
    ANIM_TETO_WALK,
    ANIM_TETO_RUN,
    NUM_TETO_ANIMS
} AnimTetoType;
extern AnimatedSprite animTeto[NUM_TETO_ANIMS];

#endif
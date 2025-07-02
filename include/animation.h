#ifndef ANIMATION_H
#define ANIMATION_H

#include "gba_typedefs.h"
#include "data.h"

//animation for sprites (modifies specifically tiles and spriteObj)
typedef struct {
    u32 animIndex;
    u32 animTimer;
    u8 isLoop;
    const u32 numOfFrames;
    const u32 *extraDuration;
    const Data *tileData;
    const Data *sprObjData;
} ALIGN4 AnimatedSprite;

void animation_update_frame(AnimatedSprite *anim, u32 duration);

#endif
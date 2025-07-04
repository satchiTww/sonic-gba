#ifndef ANIMATION_H
#define ANIMATION_H

#include "gba_typedefs.h"

typedef struct {
    const void *sprObjData;
    u32 sprObjLenght;
    const void *tileData;
    u32 tileLenght;
    u32 extraDuration;
} AnimSpriteFrame;

typedef struct {
    u8 isLoop;
    u32 numOfFrames;
    AnimSpriteFrame *frames;
} ALIGN4 AnimatedSprite;

void animation_update_frame(AnimatedSprite *anim, u32 duration, u16 *timer, u16 *index);

#endif
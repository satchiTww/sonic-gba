#ifndef ANIMATION_H
#define ANIMATION_H

#include "gba_typedefs.h"

typedef struct {
    const void *ObjShapeData;
    u32 ObjShapeDataLenght;
    const void *tileData;
    u32 tileDataLenght;
    u16 offsetX, offsetY;
    u32 delay;
} ALIGN4 AnimSpriteFrame;

typedef struct {
    u8 isLoop;
    u32 numOfFrames;
    AnimSpriteFrame *frames;
} ALIGN4 AnimatedSprite;

void animation_update_frame(AnimatedSprite *anim, u32 duration, u32 *timer, u16 *index);

#endif
#include "animation.h"
#include "gba_dma.h"
#include <stdlib.h>

void animation_update_frame(AnimatedSprite *anim, u32 duration)
{
    if (anim == NULL) return;

    anim->animTimer++;

    if (anim->animTimer >= duration + anim->extraDuration[anim->animIndex]) {
        anim->animTimer = 0;
        anim->animIndex++;

        if (anim->animIndex >= anim->numOfFrames) {
            if (anim->isLoop)
                anim->animIndex = 0;
            else
                anim->animIndex = anim->numOfFrames - 1;
        }
    }
}
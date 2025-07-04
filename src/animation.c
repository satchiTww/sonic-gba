#include "animation.h"
#include <stddef.h>

void animation_update_frame(AnimatedSprite *anim, u32 duration, u16 *timer, u16 *index)
{
    if (anim == NULL) return;

    (*timer)++;

    if (*timer >= duration + anim->frames[*index].extraDuration) {
        *timer = 0;
        (*index)++;

        if (*index >= anim->numOfFrames) {
            if (anim->isLoop)
                *index = 0;
            else
                *index = anim->numOfFrames - 1;
        }
    }
}
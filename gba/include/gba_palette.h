#ifndef GBA_PALETTE_H
#define GBA_PALETTE_H

#include "gba_video.h"

#define PAL_MEM   ((u16*)PALRAM)

#define PAL_BG_INDEX 0
#define PAL_OAM_INDEX 256

void palette_load(const u16* pal_data, int data_lenght, int pal_index);
void palette_clear(int pal_index, int pal_lenght);

INLINE void palette_set_color(int pal_index, COLOR target_color)
{
    PAL_MEM[pal_index] = target_color;
}

#endif
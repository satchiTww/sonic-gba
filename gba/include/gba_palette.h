#ifndef GBA_PALETTE_H
#define GBA_PALETTE_H

#include "gba_video.h"

#define PAL_MEM   ((u16*)PALRAM)

#define BG_PAL_INDEX 0
#define OBJ_PAL_INDEX 256

typedef struct {
    const u16 *data;
    int lenght;
    int index;
} Palette;

void load_palette(const u16* data, int lenght, int index);

#endif
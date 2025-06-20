#include "gba_palette.h"

void load_palette(const u16* data, int lenght, int index)
{
    u16 *dest = PAL_MEM + index;
    u16 *source = (u16*)data;
    for (int i = 0; i < lenght / 2; i++) {
        dest[i] = source[i];
    }
}
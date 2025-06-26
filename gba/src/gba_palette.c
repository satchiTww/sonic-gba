#include "gba_palette.h"
#include "gba_dma.h"

void load_palette(const u16* data, int lenght, int index)
{
    u16 *dest = PAL_MEM + index;
    u16 *source = (u16*)data;
    dma3_cpy(dest, source, lenght / 2, DMA_CPY16);
}
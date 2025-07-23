#include "gba_palette.h"
#include "gba_dma.h"

void palette_load(const u16* pal_data, int data_lenght, int pal_index)
{
    dma3_cpy(&PAL_MEM[pal_index], (u16*)pal_data, data_lenght >> 1, DMA_CPY16);
}

void palette_clear(int pal_index, int pal_lenght)
{
    dma3_fill(&PAL_MEM[pal_index], 0, pal_lenght, DMA_CPY16);
}
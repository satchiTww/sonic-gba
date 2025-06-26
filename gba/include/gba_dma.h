#ifndef GBA_DMA_H
#define GBA_DMA_H

#include "gba_typedefs.h"
#include "gba_registers.h"


/*========DMA_CNT BITS============*/
//type of increment dest
#define DMA_DST_RELOAD 0x00600000
//type of increment src
#define DMA_REPEAT     0x02000000
#define DMA_CPY16      0x00000000
#define DMA_CPY32      0x04000000
#define DMA_VBLANK     0x10000000
#define DMA_HBLANK     0x20000000
//irq
#define DMA_ENABLE     0x80000000

#define DMA_HDMA   (DMA_REPEAT | DMA_HBLANK | DMA_DST_RELOAD)


INLINE void dma3_cpy(void *dest, const void *src, u32 count, u32 mode)
{
    REG_DMA3CNT = 0;
    REG_DMA3SAD = (u32)src;
    REG_DMA3DAD = (u32)dest;
    REG_DMA3CNT = count | mode | DMA_ENABLE;
}

#endif
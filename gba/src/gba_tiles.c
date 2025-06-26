#include "gba_tiles.h"
#include "gba_dma.h"

void load_tileset(const u16* data, int lenght, int ch_block, int offset)
{
    u32 *dest = (u32*)(char_block(ch_block) + (u16)(offset * 0x10));
    u32 *source = (u32*)data;
    dma3_cpy(dest, source, lenght / 4, DMA_CPY32);
}

void load_tilemap(const u16* data, int lenght, int scrn_block)
{
    u32 *dest = (u32*)screen_block(scrn_block);
    u32 *source = (u32*)data;
    dma3_cpy(dest, source, lenght / 4, DMA_CPY32);
}

/*This is made specifically for loading and scrolling though big levels
 because the gba can only load a max of 1024x1024 background at once.
 In practice, this is the same method used by the Sonic Advance trilogy.
 There's definitely more efficient methods out there, but I think this one will work fine*/
void load_scroller_tilemap(const u16* data, int scrn_block, int stage_width, int x_grid, int y_grid)
{
    u16 *dest = screen_block(scrn_block);
    u16 *source = (u16*)data;
    for (int i = 0; i < 21; i++) {
        dma3_cpy(&dest[i * 32], &(source + (y_grid + i) * (stage_width / TILE_SIZE))[x_grid], 31, DMA_CPY16);
    }
}
#include "gba_tiles.h"
#include "gba_dma.h"

void tiles_load(const u16* tile_data, int data_lenght, int char_block, int tile_index)
{
    dma3_cpy(&TILE_MEM[char_block][tile_index], tile_data, data_lenght >> 2, DMA_CPY32);
}

void tiles_clear(int char_block, int tile_index, int count)
{
    dma3_fill(&TILE_MEM[tile_index], 0, count >> 1, DMA_CPY16);
}

void tiles_load_tilemap(const u16* tilemap_data, int data_lenght, int scrn_block)
{
    dma3_cpy(&SCREENBLOCK_MEM[scrn_block], tilemap_data, data_lenght >> 2, DMA_CPY32);
}

void tiles_map_clear(int scrn_block, int count)
{
    dma3_fill(&SCREENBLOCK_MEM[scrn_block], 0, count, DMA_CPY16);
}

/*This is made specifically for loading and scrolling though big levels
 because the gba can only load a max of 1024x1024 background at once.
 In practice, this is the same method used by the Sonic Advance trilogy.
 There's definitely more efficient methods out there, but I think this one will work fine*/
void tiles_tilemap_scroll(const u16* data, int scrn_block, int map_tiles_width, int xGrid, int yGrid)
{
    int horiz_scroll_size = 31;
    int vert_scroll_size = 32;
    for (int i = 0; i < 21; i++) {
        dma3_cpy(
            &SCREENBLOCK_MEM[scrn_block][i * vert_scroll_size],
            &((u16*)data + (yGrid + i) * map_tiles_width)[xGrid],
            horiz_scroll_size,
            DMA_CPY16
        );
    }
}
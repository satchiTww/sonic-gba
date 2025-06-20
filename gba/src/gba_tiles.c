#include "gba_tiles.h"

void load_tileset(const u16* data, int lenght, int ch_block, int index)
{
    u32 *dest = (u32*)(char_block(ch_block) + (u16)(index * 0x10));
    u32 *source = (u32*)data;
    for (int i = 0; i < lenght / 4; i++)
        dest[i] = source[i];
}

void load_tilemap(const u16* data, int lenght, int scrn_block)
{
    u32 *dest = (u32*)screen_block(scrn_block);
    u32 *source = (u32*)data;
    for (int i = 0; i < lenght / 4; i++)
        dest[i] = source[i];
}

/*This is made specifically for loading and scrolling though big levels
 because the gba can only load a max of 1024x1024 background at once.
 In practice, this is the same method used by the Sonic Advance trilogy.
 There's definitely more efficient methods out there, but I don't think this one will cause issues in the future*/
void load_scroller_tilemap(const u16* data, int scrn_block, int stage_width, int x_grid, int y_grid)
{
    u16 *dest = screen_block(scrn_block);
    u16 *source = (u16*)data;
    for (int i = 0; i < 21; i++)
        for (int j = 0; j < 31; j++)
            dest[i * 32 + j] = (source + (y_grid + i) * (stage_width / TILE_SIZE))[x_grid + j];
}
#include "gba_typedefs.h"
#include "gba_video.h"

/*==============PALETTE===================*/
void load_palette(const u16* palette, int pal_len, int index)
{
    u16 *dest = PAL_MEM + index;
    u16 *source = (u16*)palette;
    for (int i = 0; i < pal_len / 2; i++) {
        dest[i] = source[i];
    }
}

/*===============TILES===========================*/

void load_tileset(const u16* tileset, int tileset_len, int ch_block, int index)
{
    u32 *dest = (u32*)(char_block(ch_block) + (u16)(index * 0x10));
    u32 *source = (u32*)tileset;
    for (int i = 0; i < tileset_len / 4; i++)
        dest[i] = source[i];
}

void load_tilemap(const u16* tilemap, int tilemap_len, int scrn_block)
{
    u32 *dest = (u32*)screen_block(scrn_block);
    u32 *source = (u32*)tilemap;
    for (int i = 0; i < tilemap_len / 4; i++)
        dest[i] = source[i];
}

void draw_tilemap(Tilemap tilemap, int stage_width, int x_grid, int y_grid)
{
    u16 *dest = screen_block(tilemap.scrn_block_index);
    u16 *source = (u16*)tilemap.tilemap;
    for (int i = 0; i < 21; i++)
        for (int j = 0; j < 31; j++)
            dest[i * 32 + j] = (source + (y_grid + i) * (stage_width / TILE_SIZE))[x_grid + j];
}
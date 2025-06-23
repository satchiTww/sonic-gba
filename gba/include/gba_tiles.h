#ifndef GBA_TILES_H
#define GBA_TILES_H

#include "gba_video.h"

#define TILE_SIZE 8

#define OAM_CHARBLOCK 4 //the charblocks 0-3 are for the background. This marks where the Object charblock starts

typedef struct {
    const u16* data;
    int lenght;
    int char_block;
    int char_block_index;
} Tileset;

typedef struct {
    const u16* data;
    int lenght;
    int scrn_block_index;
} Tilemap;

void load_tileset(const u16* data, int lenght, int ch_block, int offset);
void load_tilemap(const u16* data, int lenght, int scrn_block);
void load_scroller_tilemap(const u16* data, int scrn_block, int stage_width, int x_grid, int y_grid);

//returns a block of the charblock
INLINE u16* char_block(u32 block)
{    return (u16*)(VRAM + (block*0x4000));    }

//returns a block of the screenblock
INLINE u16* screen_block(u32 block)
{    return (u16*)(VRAM + (block*0x800));    }

#endif
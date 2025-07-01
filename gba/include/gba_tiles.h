#ifndef GBA_TILES_H
#define GBA_TILES_H

#include "gba_video.h"

#define TILE_SIZE 8

#define OBJ_CHARBLOCK 4

typedef struct { u32 data[8]; }  TILE;
typedef struct { u32 data[16]; } TILE8;

typedef TILE  CHARBLOCK[512];
typedef TILE8 CHARBLOCK8[256];

#define TILE_MEM  ((CHARBLOCK*)VRAM)
#define TILE8_MEM ((CHARBLOCK8*)VRAM)

typedef u16 SCREENBLOCK[1024];

#define SCREENBLOCK_MEM ((SCREENBLOCK*)VRAM)

void tiles_load(const u16* tile_data, int data_lenght, int char_block, int tile_index);
void tiles_load_tilemap(const u16* tilemap_data, int data_lenght, int scrn_block);
void tiles_tilemap_scroll(const u16* data, int scrn_block, int map_tiles_width, int xGrid, int yGrid);

#endif
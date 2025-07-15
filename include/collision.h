#ifndef COLLISION_H
#define COLLISION_H

#include "gba_typedefs.h"

#define COLLISION_TILE_SIZE 16

#define TILE_INDEX_MASK 0x3FF
#define TILE_HFLIP_MASK 0x400
#define TILE_VFLIP_MASK 0x800

#define FLAGGED_ANGLE 255

typedef struct {
    int distance;
    u8 angle;
} SolidTile;

typedef struct {
    u16 tileIndex;
    u8 isHflip;
    u8 isVflip;
    u8 height;
    //u8 width;
    u8 angle;
} TileInfo;

SolidTile collision_find_vertical_tile(
    int xPos, int yPos,
    const int mapWidth,
    const u16 *collisionMapData,
    const u8 *heightData,
    const u8 *angleData
);

TileInfo collision_get_tile_info(
    int xPos, int yPos,
    const int mapWidth,
    const u16 *collisionMapData,
    const u8 *heightData,
    //const u8 *widthData,
    const u8 *angleData
);

#endif
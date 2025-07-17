#ifndef COLLISION_H
#define COLLISION_H

#include "gba_typedefs.h"
#include "stage.h"

#define COLLISION_TILE_SIZE 16

#define TILE_INDEX_MASK 0x3FF
#define TILE_HFLIP_MASK 0x400
#define TILE_VFLIP_MASK 0x800

#define FLAGGED_ANGLE 255

typedef enum {
    COLL_UP = -1,
    COLL_DOWN = 1,
} CollisionFloorDir;

typedef enum {
    COLL_LEFT = -1,
    COLL_RIGHT = 1,
} CollisionWallDir;

typedef struct {
    int distance;
    u8 angle;
} SolidTile;

typedef struct {
    u16 tileIndex;
    u8 isHflip;
    u8 isVflip;
    s8 height;
    s8 width;
    u8 angle;
} TileInfo;

SolidTile collision_find_vertical_tile(int x, int y, const Stage *stage, CollisionFloorDir dir);
SolidTile collision_find_horizontal_tile(int x, int y, const Stage *stage, CollisionWallDir dir);

TileInfo collision_get_tile_info(int x, int y, const Stage *stage);

#endif
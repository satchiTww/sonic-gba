#include "collision.h"

INLINE int get_tile_height(int x, const TileInfo *tileInfo, const u8 *heightData)
{
    int heightIndex = tileInfo->isHflip ? (COLLISION_TILE_SIZE - 1) - x % COLLISION_TILE_SIZE : x % COLLISION_TILE_SIZE;
    int height = heightData[tileInfo->tileIndex * COLLISION_TILE_SIZE + heightIndex];

    if (tileInfo->isVflip) height = -height;

    return height;
}

INLINE int get_tile_width(int y, const TileInfo *tileInfo, const u8 *widthData)
{
    int widthIndex = tileInfo->isVflip ? (COLLISION_TILE_SIZE - 1) - y % COLLISION_TILE_SIZE : y % COLLISION_TILE_SIZE;
    int width = widthData[tileInfo->tileIndex * COLLISION_TILE_SIZE + widthIndex];

    if (tileInfo->isHflip) width = -width;

    return width;
}

INLINE u8 get_tile_angle(const TileInfo *tileInfo, const u8 *angleData)
{
    u8 angle = angleData[tileInfo->tileIndex];

    if (tileInfo->isVflip) angle  = (-(angle + 64)) - 64;
    if (tileInfo->isHflip) angle  = ~angle;

    return angle;
}

SolidTile find_v_tile2(int x, int y, const Stage *stage)
{
    if (x < 0 || y < 0 || x > stage->mapWidth || y > stage->mapHeight) return (SolidTile){0};

    TileInfo tile;
    int height;
    u8 angle;

    tile = collision_get_tile_info(x/COLLISION_TILE_SIZE, y/COLLISION_TILE_SIZE, stage);

    height = get_tile_height(x, &tile, stage->collisionHeightData);
    angle = get_tile_angle(&tile, stage->collisionAngleData);

    if (height > 0) {
        int tileSurface = COLLISION_TILE_SIZE - (height + y % COLLISION_TILE_SIZE);
        
        return (SolidTile){tileSurface, angle};
    }

    //no tile found
    int tileEdge = COLLISION_TILE_SIZE - (y % COLLISION_TILE_SIZE);
    return (SolidTile){tileEdge, angle};
}

SolidTile collision_find_vertical_tile(int x, int y, const Stage *stage, CollisionFloorDir dir)
{
    if (x < 0 || y < 0 || x > stage->mapWidth || y > stage->mapHeight) return (SolidTile){0};

    SolidTile tileFound;
    TileInfo tile;
    int height;
    u8 angle;

    tile = collision_get_tile_info(x/COLLISION_TILE_SIZE, y/COLLISION_TILE_SIZE, stage);

    height = get_tile_height(x, &tile, stage->collisionHeightData);
    angle = get_tile_angle(&tile, stage->collisionAngleData);

    if (height > 0) //height found is between 1 and 16
    {
        if (height != COLLISION_TILE_SIZE) { //normal tile, process this tile
            tileFound.distance = COLLISION_TILE_SIZE - (height + y % COLLISION_TILE_SIZE);
            tileFound.angle    = angle;

            return tileFound;
        }
        else { //full tile, check tile above
            tileFound = find_v_tile2(x, y - COLLISION_TILE_SIZE, stage);
            tileFound.distance -= COLLISION_TILE_SIZE;

            return tileFound;
        }
    }

    //height is 0 (no tile found, check tile bellow)
    tileFound = find_v_tile2(x, y + COLLISION_TILE_SIZE, stage);
    tileFound.distance += COLLISION_TILE_SIZE;
    return tileFound;
}

SolidTile find_h_tile2(int x, int y, const Stage *stage, CollisionWallDir dir)
{
    if (x < 0 || y < 0 || x > stage->mapWidth || y > stage->mapHeight) return (SolidTile){0};

    TileInfo tile;
    int width;
    u8 angle;

    tile = collision_get_tile_info(x/COLLISION_TILE_SIZE, y/COLLISION_TILE_SIZE, stage);

    width = get_tile_width(y, &tile, stage->collisionWidthData);
    angle = get_tile_angle(&tile, stage->collisionAngleData);

    if (width > 0) {
        int tileSurface = dir > 0 ? COLLISION_TILE_SIZE - (width + x % COLLISION_TILE_SIZE) : x % COLLISION_TILE_SIZE - width;
        
        return (SolidTile){tileSurface, angle};
    }

    //no tile found
    int tileEdge = dir > 0 ? COLLISION_TILE_SIZE - (x % COLLISION_TILE_SIZE) : x % COLLISION_TILE_SIZE;

    return (SolidTile){tileEdge, angle};
}

SolidTile collision_find_horizontal_tile(int x, int y, const Stage *stage, CollisionWallDir dir)
{
    if (x < 0 || y < 0 || x > stage->mapWidth || y > stage->mapHeight) return (SolidTile){0};

    SolidTile tileFound;
    TileInfo tile;
    int width;
    u8 angle;

    tile = collision_get_tile_info(x/COLLISION_TILE_SIZE, y/COLLISION_TILE_SIZE, stage);
    width = get_tile_width(y, &tile, stage->collisionWidthData);
    angle = get_tile_angle(&tile, stage->collisionAngleData);

    if (width > 0)
    {
        if (width != COLLISION_TILE_SIZE) { //not a full tile
            tileFound.distance = dir > 0 ? COLLISION_TILE_SIZE - (width + x % COLLISION_TILE_SIZE) : x % COLLISION_TILE_SIZE - width;
            tileFound.angle = angle;

            return tileFound;
        }
        else { //full tile
            tileFound = find_h_tile2(x - COLLISION_TILE_SIZE * dir, y, stage, dir);
            tileFound.distance -= COLLISION_TILE_SIZE;

            return tileFound;
        }
    }

    //width is 0 (no tile found, check tile in front)
    tileFound = find_h_tile2(x + COLLISION_TILE_SIZE * dir, y, stage, dir);
    tileFound.distance += COLLISION_TILE_SIZE;

    return tileFound;
}

TileInfo collision_get_tile_info(int gridX, int gridY, const Stage *stage)
{
    if (gridX < 0 || gridY < 0 || gridX > stage->mapWidth/COLLISION_TILE_SIZE || gridY > stage->mapHeight/COLLISION_TILE_SIZE) return (TileInfo){0};

    TileInfo tileInfo;

    u16 tileEntry   = stage->collisionMapData[gridY * (stage->mapWidth/COLLISION_TILE_SIZE) + gridX];
    u16 tileIndex   = tileEntry & TILE_INDEX_MASK;
    u8 isHflip      = (tileEntry & TILE_HFLIP_MASK) != 0;
    u8 isVflip      = (tileEntry & TILE_VFLIP_MASK) != 0;

    tileInfo.tileIndex = tileIndex;
    tileInfo.isHflip   = isHflip;
    tileInfo.isVflip   = isVflip;

    return tileInfo;
}
#include "collision.h"

SolidTile find_v_tile2(int x, int y, const Stage *stage)
{
    if (x < 0 || y < 0 || x > stage->mapWidth || y > stage->mapHeight) return (SolidTile){0};

    TileInfo tileInfo = collision_get_tile_info(x, y, stage);

    if (tileInfo.height > 0) {
        int tileSurface = COLLISION_TILE_SIZE - (tileInfo.height + y % COLLISION_TILE_SIZE);
        
        return (SolidTile){tileSurface, tileInfo.angle};
    }

    //no tile found
    int tileEdge = COLLISION_TILE_SIZE - (y % COLLISION_TILE_SIZE);
    return (SolidTile){tileEdge, tileInfo.angle};
}

SolidTile collision_find_vertical_tile(int x, int y, const Stage *stage, CollisionFloorDir dir)
{
    if (x < 0 || y < 0 || x > stage->mapWidth || y > stage->mapHeight) return (SolidTile){0};

    SolidTile tileFound;

    TileInfo tileInfo = collision_get_tile_info(x, y, stage);

    if (tileInfo.height > 0) //height found is between 1 and 16
    {
        if (tileInfo.height != COLLISION_TILE_SIZE) { //normal tile, process this tile
            tileFound.distance = COLLISION_TILE_SIZE - (tileInfo.height + y % COLLISION_TILE_SIZE);
            tileFound.angle = tileInfo.angle;

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

    TileInfo tileInfo = collision_get_tile_info(x, y, stage);

    if (!tileInfo.isHflip && dir == COLL_LEFT) {
        tileInfo.width = -tileInfo.width;
    }

    if (tileInfo.width > 0) {
        int tileSurface = COLLISION_TILE_SIZE - (tileInfo.width + x % COLLISION_TILE_SIZE);
        
        return (SolidTile){tileSurface, tileInfo.angle};
    }
    else if (tileInfo.width < 0) {
        int tileSurface = tileInfo.width + x % COLLISION_TILE_SIZE;

        if (tileSurface < 0) {
            return (SolidTile){tileSurface, tileInfo.angle};
        }
    }

    //no tile found
    int tileEdge = dir == COLL_RIGHT ? COLLISION_TILE_SIZE - (x % COLLISION_TILE_SIZE) : x % COLLISION_TILE_SIZE;
    return (SolidTile){tileEdge, tileInfo.angle};
}

SolidTile collision_find_horizontal_tile(int x, int y, const Stage *stage, CollisionWallDir dir)
{
    if (x < 0 || y < 0 || x > stage->mapWidth || y > stage->mapHeight) return (SolidTile){0};

    SolidTile tileFound;

    TileInfo tileInfo = collision_get_tile_info(x, y, stage);

    if (!tileInfo.isHflip && dir == COLL_LEFT) {
        tileInfo.width = -tileInfo.width;
    }

    if (tileInfo.width > 0)
    {
        if (tileInfo.width != COLLISION_TILE_SIZE) {
            tileFound.distance = COLLISION_TILE_SIZE - (tileInfo.width + x % COLLISION_TILE_SIZE);
            tileFound.angle = tileInfo.angle;

            return tileFound;
        }
        else {
            tileFound = find_h_tile2(x - COLLISION_TILE_SIZE * dir, y, stage, dir);
            tileFound.distance -= COLLISION_TILE_SIZE;

            return tileFound;
        }
    }
    else if (tileInfo.width < 0)
    {
        if (tileInfo.width != -COLLISION_TILE_SIZE) {
            tileFound.distance = tileInfo.width + x % COLLISION_TILE_SIZE;
            tileFound.angle = tileInfo.angle;

            return tileFound;
        }
        else {
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

TileInfo collision_get_tile_info(int x, int y, const Stage *stage)
{
    if (x < 0 || y < 0 || x > stage->mapWidth || y > stage->mapHeight) return (TileInfo){0};

    TileInfo tileInfo;

    int gridX = x / COLLISION_TILE_SIZE;
    int gridY = y / COLLISION_TILE_SIZE;

    u16 tileEntry   = stage->collisionMapData[gridY * (stage->mapWidth/COLLISION_TILE_SIZE) + gridX];
    u16 tileIndex   = tileEntry & TILE_INDEX_MASK;
    u8 isHflip      = (tileEntry & TILE_HFLIP_MASK) != 0;
    u8 isVflip      = (tileEntry & TILE_VFLIP_MASK) != 0;


    u8 heightIndex = isHflip ? 
        gridX * COLLISION_TILE_SIZE + (COLLISION_TILE_SIZE - 1) - x : 
        x - gridX * COLLISION_TILE_SIZE
    ;
    u8 widthIndex = isVflip ? gridY * COLLISION_TILE_SIZE + (COLLISION_TILE_SIZE - 1) - y :
    y - gridY * COLLISION_TILE_SIZE
    ;

    s8 height = stage->collisionHeightData[tileIndex * COLLISION_TILE_SIZE + heightIndex];
    s8 width  = stage->collisionWidthData[tileIndex * COLLISION_TILE_SIZE + widthIndex];
    u8 angle  = stage->collisionAngleData[tileIndex];

    if (isVflip) {
        height = -height;
        angle  = (-(angle + 64)) - 64;
    }
    if (isHflip) {
        width = -width;
        angle = ~angle;
    }

    tileInfo.tileIndex = tileIndex;
    tileInfo.isHflip   = isHflip;
    tileInfo.isVflip   = isVflip;
    tileInfo.height    = height;
    tileInfo.width     = width;
    tileInfo.angle     = angle;

    return tileInfo;
}
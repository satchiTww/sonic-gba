#include "collision.h"

SolidTile collision_find_vertical_tile(
    int xPos, int yPos,
    const int mapWidth,
    const u16 *collisionMapData,
    const u8 *heightData,
    const u8 *angleData)
{
    if (xPos < 0 || yPos < 0 || xPos > mapWidth * COLLISION_TILE_SIZE) return (SolidTile){0};

    SolidTile tileFound;

    int gridY = yPos / COLLISION_TILE_SIZE;

    TileInfo tileInfo = collision_get_tile_info(xPos, gridY * COLLISION_TILE_SIZE, mapWidth, collisionMapData, heightData, angleData);

    if (tileInfo.height == 0) {
        tileInfo = collision_get_tile_info(xPos, ++gridY * COLLISION_TILE_SIZE, mapWidth, collisionMapData, heightData, angleData);
    }
    if (tileInfo.height == COLLISION_TILE_SIZE) {
        tileInfo = collision_get_tile_info(xPos, --gridY * COLLISION_TILE_SIZE, mapWidth, collisionMapData, heightData, angleData);

        if (tileInfo.height == 0) {
            tileInfo = collision_get_tile_info(xPos, ++gridY * COLLISION_TILE_SIZE, mapWidth, collisionMapData, heightData, angleData);
        }
    }

    tileFound.distance = gridY * COLLISION_TILE_SIZE + COLLISION_TILE_SIZE - tileInfo.height - yPos;
    tileFound.angle = tileInfo.angle;

    return tileFound;
}

TileInfo collision_get_tile_info(
    int xPos, int yPos,
    const int mapWidth,
    const u16 *collisionMapData,
    const u8 *heightData,
    //const u8 *widthData,
    const u8 *angleData
)
{
    if (xPos < 0 || yPos < 0 || xPos > mapWidth * COLLISION_TILE_SIZE) return (TileInfo){0};

    TileInfo tileInfo;

    int gridX = xPos / COLLISION_TILE_SIZE;
    int gridY = yPos / COLLISION_TILE_SIZE;

    u16 tileEntry = collisionMapData[gridY * mapWidth + gridX];
    u16 tileIndex   = tileEntry & TILE_INDEX_MASK;
    u8 isHflip      = (tileEntry & TILE_HFLIP_MASK) != 0;
    u8 isVflip      = (tileEntry & TILE_VFLIP_MASK) != 0;

    u8 heightIndex = isHflip ? 
        gridX * COLLISION_TILE_SIZE + (COLLISION_TILE_SIZE - 1) - xPos : 
        xPos - gridX * COLLISION_TILE_SIZE
    ;

    u8 height       = heightData[tileIndex * COLLISION_TILE_SIZE + heightIndex];
    u8 angle        = isHflip ? -angleData[tileIndex] : angleData[tileIndex];

    tileInfo.tileIndex = tileIndex;
    tileInfo.isHflip   = isHflip;
    tileInfo.isVflip   = isVflip;
    tileInfo.height    = height;
    //todo: width
    tileInfo.angle     = angle;

    return tileInfo;
}
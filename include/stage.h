#ifndef STAGE_H
#define STAGE_H

#include "gba_typedefs.h"

typedef struct {
    const int mapWidth;
    const int mapHeight;
    const u16 *collisionMapData;
    const u8 *collisionHeightData;
    const u8 *collisionWidthData;
    const u8 *collisionAngleData;
} Stage;

extern Stage stageTestRoom;

#endif
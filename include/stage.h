#ifndef STAGE_H
#define STAGE_H

#include "gba_typedefs.h"

typedef struct {
    int mapWidth;
    int mapHeight;
    const u16* tilemap;
} Stage;


#endif
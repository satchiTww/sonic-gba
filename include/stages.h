#ifndef STAGES_H
#define STAGES_H

#include "gba_typedefs.h"

#include "data/tilemaps/TestZone.h"

typedef struct {
    int mapWidth;
    int mapHeight;
    const u16* tilemap_data;
} Stage;

extern Stage testZone;

#endif
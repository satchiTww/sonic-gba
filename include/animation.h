#ifndef ANIMATION_H
#define ANIMATION_H

#include "gba_typedefs.h"
#include "gba_tiles.h"
#include "sprite.h"

typedef struct {
    int numOfFrames;
    int isLoop;
    int *frameDuration;
    Tileset *frameTiles;
} AnimatedTiles;

void animation_tiles_play(const AnimatedTiles animTileset);

#endif
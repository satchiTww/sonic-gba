#ifndef SPRITE_H
#define SPRITE_H

#include "gba_palette.h"
#include "gba_tiles.h"
#include "gba_objects.h"

typedef struct {
    const Palette palette;
    const Tileset tileset;
} Sprite;

void load_sprite(Sprite *sprite);

#endif
#ifndef SPRITE_H
#define SPRITE_H

#include "gba_video.h"

typedef struct {
    const Palette palette;
    const Tileset tileset;
} Sprite;

void load_sprite(Sprite *sprite);

#endif
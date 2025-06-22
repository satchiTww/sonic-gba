#ifndef SPRITE_H
#define SPRITE_H

#include "gba_palette.h"
#include "gba_tiles.h"
#include "gba_objects.h"

typedef struct {
    u8 xPos; //in px
    u8 yPos; //in px
    int width; //in tiles
    int height; //in tiles
    int objPriority;
    int bgPriority;
    const Palette palette;
    const Tileset tileset;
    int objCount;
    OBJ_ATTR *obj;
} Sprite;

void load_sprite(Sprite *sprite, u8 xPos, u8 yPos, int objPriority, int bgPriority);

#endif
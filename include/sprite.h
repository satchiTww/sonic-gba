#ifndef SPRITE_H
#define SPRITE_H

#include "gba_palette.h"
#include "gba_tiles.h"
#include "gba_objects.h"

//TODO: Affine Sprites

//struct for a object that makes a sprite
typedef struct {
    int offsetX;
    int offsetY;
    OBJ_ATTR attributes;
} SpriteObj;

typedef struct {
    u32 xPos; //in px
    u32 yPos; //in px
    int width; //in tiles
    int height; //in tiles
    int objPriority; //aka oam ID 0 - 128
    int bgPriority;
    const Palette palette;
    const Tileset tileset;
    int objCount;
    SpriteObj *obj;
} Sprite;

void load_sprite(Sprite *sprite, u32 xPos, u32 yPos, int objPriority, int bgPriority);
void sprite_update_oam(Sprite *sprite);
void sprite_set_pos(Sprite *sprite, u32 xPos, u32 yPos);

#endif
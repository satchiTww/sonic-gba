#include "sprite.h"

void load_sprite(Sprite *sprite, u32 xPos, u32 yPos, int objPriority, int bgPriority)
{
    load_palette(
        sprite->palette.data,
        sprite->palette.lenght,
        sprite->palette.index
    );
    load_tileset(
        sprite->tileset.data,
        sprite->tileset.lenght,
        sprite->tileset.char_block,
        sprite->tileset.char_block_index
    );
    sprite->xPos = xPos;
    sprite->yPos = yPos;
    sprite->objPriority = objPriority;
    sprite->bgPriority = bgPriority;

    //todo: update oam
}

//set the position of a sprite
void sprite_set_pos(Sprite *sprite, u32 xPos, u32 yPos)
{
    sprite->xPos = xPos;
    sprite->yPos = yPos;

    for (int i = 0; i < sprite->objCount; i++) {
        int objX = sprite->obj[i].offsetX + sprite->xPos;
        int objY = sprite->obj[i].offsetY + sprite->yPos;

        obj_set_pos(&sprite->obj[i].attributes, objX, objY);

        obj_buffer[sprite->objPriority + i] = sprite->obj[i].attributes;
    }
}
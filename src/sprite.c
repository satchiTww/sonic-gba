#include "sprite.h"

void load_sprite(Sprite *sprite, u8 xPos, u8 yPos, int objPriority, int bgPriority)
{
    load_palette(
        sprite->palette.data,
        sprite->palette.lenght,
        sprite->palette.index
    );
    load_tileset(sprite->tileset.data,
        sprite->tileset.lenght,
        sprite->tileset.char_block,
        sprite->tileset.char_block_index
    );
    for (int i = 0; i < sprite->objCount; i++) {
        obj_set_pos(&sprite->obj[i], sprite->obj[i].xPos + xPos, sprite->obj[i].yPos + yPos);
        sprite->obj[i].bgPriority = bgPriority;
        obj_buffer[objPriority + i] = sprite->obj[i];
    }
}
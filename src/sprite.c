#include "sprite.h"
#include "gba_dma.h"

void sprite_load_pal(Sprite *sprite)
{
    palette_load(sprite->palette.data, sprite->palette.lenght, sprite->palette.index);
}

void sprite_load_tileset(Sprite *sprite)
{
    //tiles_load(
    //    sprite->tileset.data,
    //    sprite->tileset.lenght,
    //    sprite->tileset.char_block_offset
    //);
}

void sprite_load_obj(Sprite *sprite)
{
    for (int i = 0; i < sprite->objCount; i++)
        dma3_cpy(&obj_buffer[sprite->objPriority + i], &sprite->obj[i], 1, DMA_CPY16);
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
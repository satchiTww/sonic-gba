#include "sprite.h"

void load_sprite(Sprite *sprite)
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
    //TODO: load OAM
}
#include "sprite.h"
#include "data/gfx/sprites/teto/teto_pal.h"
#include "data/gfx/sprites/teto/walk/teto_walk.h"

static SpriteObj walk_obj_00[2]=
{
    [0].attributes.shape = OBJ_SHAPE_SQUARE,
    [0].attributes.size = OBJ_SIZE_2,

    [1].offsetY = 32,
    [1].attributes.yPos = 32,
    [1].attributes.shape = OBJ_SHAPE_WIDE,
    [1].attributes.size = OBJ_SIZE_2,
    [1].attributes.tileID = 16,
};

Sprite spr_teto_walk[8]=
{
    //frame 0
    [0].width = 4,
    [0].height = 6,
    [0].palette=
    {
        .data = teto_pal,
        .index = PAL_OBJ_INDEX,
        .lenght = teto_palLen
    },
    [0].tileset=
    {
        .data = teto_walk_01Tiles,
        .lenght = teto_walk_01TilesLen,
        .char_block = 4,
    },
    [0].objCount = 2,
    [0].obj = walk_obj_00
};

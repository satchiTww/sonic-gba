#include "sprite.h"
#include "data/sprites/sonic.h"

static SpriteObj sprObjSonic[2]=
{
    [0].offsetX = 0,
    [0].offsetY = 0,
    [0].attributes.shape = OBJ_SHAPE_SQUARE,
    [0].attributes.size = OBJ_SIZE_2,
    [0].attributes.tileID = 0,

    [1].offsetX = 0,
    [1].offsetY = 32,
    [1].attributes.shape = OBJ_SHAPE_WIDE,
    [1].attributes.size = OBJ_SIZE_1,
    [1].attributes.tileID = 16,
};

Sprite sprSonic=
{
    .width = 4,
    .height = 5,
    .palette=
    {
        .data = sonicPal,
        .lenght = sonicPalLen,
        .index = OBJ_PAL_INDEX + 0
    },
    .tileset=
    {
        .data = sonicTiles,
        .lenght = sonicTilesLen,
        .char_block = OAM_CHARBLOCK,
        .char_block_index = 0
    },
    .objCount = 2,
    .obj = sprObjSonic
};
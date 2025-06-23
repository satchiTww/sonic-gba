#include "sprite.h"
#include "data/sprites/teto.h"

static SpriteObj sprObjTeto[2]=
{
    [0].offsetX = 0,
    [0].offsetY = 0,
    [0].attributes.shape = OBJ_SHAPE_SQUARE,
    [0].attributes.size = OBJ_SIZE_2,
    [0].attributes.tileID = 0,

    [1].offsetX = 0,
    [1].offsetY = 32,
    [1].attributes.shape = OBJ_SHAPE_WIDE,
    [1].attributes.size = OBJ_SIZE_2,
    [1].attributes.tileID = 16,
};

Sprite sprTeto=
{
    .width = 4,
    .height = 6,
    .palette=
    {
        .data = tetoPal,
        .lenght = tetoPalLen,
        .index = OBJ_PAL_INDEX
    },
    .tileset=
    {
        .data = tetoTiles,
        .lenght = tetoTilesLen,
        .char_block = OAM_CHARBLOCK,
        .char_block_index = 0
    },
    .objCount = 2,
    .obj = sprObjTeto
};
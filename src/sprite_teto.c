#include "sprite.h"
#include "data/sprites/teto.h"

static OBJ_ATTR obj_sprTeto[2]=
{
    [0].shape = OBJ_SHAPE_SQUARE,
    [0].size = OBJ_SIZE_2,

    [1].yPos = 32,
    [1].shape = OBJ_SHAPE_WIDE,
    [1].size = OBJ_SIZE_2,
    [1].tileID = 16,
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
    .obj = obj_sprTeto
};
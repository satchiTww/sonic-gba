#include "sprite.h"
#include "data/sprites/teto.h"

Sprite sprTeto=
{
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
    }
};
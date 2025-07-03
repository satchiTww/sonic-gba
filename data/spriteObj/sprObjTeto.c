#include "data/spriteObj/sprObjTeto.h"
#include "gba_objects.h"

const SpriteObj teto_idle_oam00[2]=
{
    [0].format = OBJ_32x32,

    [1].format = OBJ_32x16,
    [1].offsetY = 32,
    [1].offsetTileID = 16,
};

const SpriteObj teto_run_oam[2]=
{
    [0].format = OBJ_32x32,
    [0].offsetY = 8,

    [1].format = OBJ_32x8,
    [1].offsetY = 40,
    [1].offsetTileID = 16,
};

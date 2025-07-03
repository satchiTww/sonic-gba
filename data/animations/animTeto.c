#include "animation.h"
#include "data/spriteObj/sprObjTeto.h"
#include "data/sprites.h"

//idle
static const u32 idleExtraFrameDuration = 0;

static const Data idleSprObj=
{
    .data = teto_idle_oam00,
    .size = teto_idle_oam00_lenght,
};
static const Data idleTiles=
{
    .data = teto_idleTiles,
    .size = (u32)_sizeof_teto_idleTiles,
};

AnimatedSprite animSpriteTetoIdle=
{
    .numOfFrames = 1,
    .isLoop = TRUE,
    .extraDuration = (u32*)&idleExtraFrameDuration,
    .sprObjData = (Data*)&idleSprObj,
    .tileData = (Data*)&idleTiles,
};

//run
static const u32 runExtraFrameDuration[4] = {0, 0, 0, 0};

static const Data runSprObj[4]=
{
    [0].data = teto_run_oam,
    [0].size = teto_run_oam_lenght,

    [1].data = teto_run_oam,
    [1].size = teto_run_oam_lenght,

    [2].data = teto_run_oam,
    [2].size = teto_run_oam_lenght,

    [3].data = teto_run_oam,
    [3].size = teto_run_oam_lenght,
};
static const Data runTiles[4]=
{
    [0].data = teto_run0Tiles,
    [0].size = (u32)_sizeof_teto_run0Tiles,

    [1].data = teto_run1Tiles,
    [1].size = (u32)_sizeof_teto_run0Tiles,

    [2].data = teto_run2Tiles,
    [2].size = (u32)_sizeof_teto_run0Tiles,

    [3].data = teto_run3Tiles,
    [3].size = (u32)_sizeof_teto_run0Tiles,
};

AnimatedSprite animSpriteTetoRun=
{
    .numOfFrames = 4,
    .isLoop = TRUE,
    .extraDuration = (u32*)runExtraFrameDuration,
    .sprObjData = (Data*)runSprObj,
    .tileData = (Data*)runTiles,
};
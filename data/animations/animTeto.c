#include "animation.h"
#include "data/spriteObj/sprObjTeto.h"
#include "data/gfx/sprites/teto/idle/teto_idle_tiles.h"
#include "data/gfx/sprites/teto/run/teto_run.h"

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
    .size = teto_idleTilesLen,
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
    [0].data = teto_run_00Tiles,
    [0].size = teto_run_00TilesLen,

    [1].data = teto_run_01Tiles,
    [1].size = teto_run_01TilesLen,

    [2].data = teto_run_02Tiles,
    [2].size = teto_run_02TilesLen,

    [3].data = teto_run_03Tiles,
    [3].size = teto_run_03TilesLen,
};

AnimatedSprite animSpriteTetoRun=
{
    .numOfFrames = 4,
    .isLoop = TRUE,
    .extraDuration = (u32*)runExtraFrameDuration,
    .sprObjData = (Data*)runSprObj,
    .tileData = (Data*)runTiles,
};
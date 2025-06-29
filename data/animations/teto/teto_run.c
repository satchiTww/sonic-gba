#include "teto_run.h"
#include "data/gfx/sprites/teto/run/teto_run.h"

//tiles
static Tileset teto_run_tiles[4]=
{
    [0].data = teto_run_00Tiles,
    [0].lenght = teto_run_00TilesLen,
    [0].char_block = 4,
    [0].char_block_offset = 0,

    [1].data = teto_run_01Tiles,
    [1].lenght = teto_run_01TilesLen,
    [1].char_block = 4,
    [1].char_block_offset = 0,

    [2].data = teto_run_02Tiles,
    [2].lenght = teto_run_02TilesLen,
    [2].char_block = 4,
    [2].char_block_offset = 0,

    [3].data = teto_run_03Tiles,
    [3].lenght = teto_run_03TilesLen,
    [3].char_block = 4,
    [3].char_block_offset = 0,
};

static int frame_dur[4] = {1, 1, 1, 1};

AnimatedTiles animTilesTetoRun=
{
    .numOfFrames = 4,
    .isLoop = 1,
    .frameDuration = frame_dur,
    .frameTiles = teto_run_tiles
};

/*
//sprites
static SpriteObj sprObjRun[4][2]=
{
    //frame 0
    //obj 0
    [0][0].attributes.shape = OBJ_SHAPE_SQUARE,
    [0][0].attributes.size = OBJ_SIZE_2,
    //obj 1
    [0][1].attributes.shape = OBJ_SHAPE_WIDE,
    [0][1].attributes.size = OBJ_SIZE_2,
    [0][1].attributes.tileID = 16,
    [0][1].offsetY = 32,

    //frame 1
    //obj 0
    [1][0].attributes.shape = OBJ_SHAPE_SQUARE,
    [1][0].attributes.size = OBJ_SIZE_2,
    //obj 1
    [1][1].attributes.shape = OBJ_SHAPE_WIDE,
    [1][1].attributes.size = OBJ_SIZE_2,
    [1][1].attributes.tileID = 16,
    [1][1].offsetY = 32,

    //frame 2
    //obj 0
    [2][0].attributes.shape = OBJ_SHAPE_SQUARE,
    [2][0].attributes.size = OBJ_SIZE_2,
    //obj 1
    [2][1].attributes.shape = OBJ_SHAPE_WIDE,
    [2][1].attributes.size = OBJ_SIZE_2,
    [2][1].attributes.tileID = 16,
    [2][1].offsetY = 32,

    //frame 3
    //obj 0
    [3][0].attributes.shape = OBJ_SHAPE_SQUARE,
    [3][0].attributes.size = OBJ_SIZE_2,
    //obj 1
    [3][1].attributes.shape = OBJ_SHAPE_WIDE,
    [3][1].attributes.size = OBJ_SIZE_2,
    [3][1].attributes.tileID = 16,
    [3][1].offsetY = 32,
};

static int obj_count[4] = {2, 2, 2, 2};

AnimatedSprite animSpriteTetoRun=
{
    .numOfFrames = 4,
    .isLoop = 1,
    .frameDuration = frame_dur,
    .frameObjCount = obj_count,
    .frameObjs = sprObjRun,
};
*/
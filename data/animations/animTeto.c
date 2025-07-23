#include "data/include/animation_data.h"
#include "data/include/obj_shape_data.h"
#include "data/include/sprite_data.h"

static const AnimSpriteFrame idleFrames[] = {
    { teto_idleObjShapes, (u32)_sizeof_teto_idleObjShapes, teto_idleTiles, (u32)_sizeof_teto_idleTiles, -2, -4, 0},
};

static const AnimSpriteFrame walkFrames[] = {
    {teto_affineObjShapes, (u32)_sizeof_teto_affineObjShapes, teto_walk0Tiles, (u32)_sizeof_teto_walk0Tiles, -2, -2, 0},
    {teto_affineObjShapes, (u32)_sizeof_teto_affineObjShapes, teto_walk1Tiles, (u32)_sizeof_teto_walk1Tiles, -2, -2, 0},
    {teto_affineObjShapes, (u32)_sizeof_teto_affineObjShapes, teto_walk2Tiles, (u32)_sizeof_teto_walk2Tiles, -2, -2, 0},
    {teto_affineObjShapes, (u32)_sizeof_teto_affineObjShapes, teto_walk3Tiles, (u32)_sizeof_teto_walk3Tiles, -2, -2, 0},
    {teto_affineObjShapes, (u32)_sizeof_teto_affineObjShapes, teto_walk4Tiles, (u32)_sizeof_teto_walk4Tiles, -2, -2, 0},
    {teto_affineObjShapes, (u32)_sizeof_teto_affineObjShapes, teto_walk5Tiles, (u32)_sizeof_teto_walk5Tiles, -2, -2, 0},
    {teto_affineObjShapes, (u32)_sizeof_teto_affineObjShapes, teto_walk6Tiles, (u32)_sizeof_teto_walk6Tiles, -2, -2, 0},
    {teto_affineObjShapes, (u32)_sizeof_teto_affineObjShapes, teto_walk7Tiles, (u32)_sizeof_teto_walk7Tiles, -2, -2, 0},
};

static const AnimSpriteFrame runFrames[] = {
    { teto_affineObjShapes, (u32)_sizeof_teto_affineObjShapes, teto_run0Tiles, (u32)_sizeof_teto_run0Tiles, -2, -2, 0},
    { teto_affineObjShapes, (u32)_sizeof_teto_affineObjShapes, teto_run1Tiles, (u32)_sizeof_teto_run1Tiles, -2, -2, 0},
    { teto_affineObjShapes, (u32)_sizeof_teto_affineObjShapes, teto_run2Tiles, (u32)_sizeof_teto_run2Tiles, -2, -2, 0},
    { teto_affineObjShapes, (u32)_sizeof_teto_affineObjShapes, teto_run3Tiles, (u32)_sizeof_teto_run3Tiles, -2, -2, 0},
};

static const AnimSpriteFrame pushFrames[] = {
    { teto_pushObjShapes, (u32)_sizeof_teto_pushObjShapes, teto_push0Tiles, (u32)_sizeof_teto_push0Tiles, -5, -4, 0},
    { teto_pushObjShapes, (u32)_sizeof_teto_pushObjShapes, teto_push1Tiles, (u32)_sizeof_teto_push1Tiles, -5, -4, 0},
    { teto_pushObjShapes, (u32)_sizeof_teto_pushObjShapes, teto_push2Tiles, (u32)_sizeof_teto_push2Tiles, -5, -4, 0},
    { teto_pushObjShapes, (u32)_sizeof_teto_pushObjShapes, teto_push3Tiles, (u32)_sizeof_teto_push3Tiles, -5, -4, 0},
};

static const AnimSpriteFrame rollFrames[] = {
    {teto_rollObjShapes, (u32)_sizeof_teto_rollObjShapes, teto_roll0Tiles, (u32)_sizeof_teto_roll0Tiles, 0, 0, 0},
    {teto_rollObjShapes, (u32)_sizeof_teto_rollObjShapes, teto_roll4Tiles, (u32)_sizeof_teto_roll4Tiles, 0, 0, 0},
    {teto_rollObjShapes, (u32)_sizeof_teto_rollObjShapes, teto_roll1Tiles, (u32)_sizeof_teto_roll1Tiles, 0, 0, 0},
    {teto_rollObjShapes, (u32)_sizeof_teto_rollObjShapes, teto_roll4Tiles, (u32)_sizeof_teto_roll4Tiles, 0, 0, 0},
    {teto_rollObjShapes, (u32)_sizeof_teto_rollObjShapes, teto_roll2Tiles, (u32)_sizeof_teto_roll2Tiles, 0, 0, 0},
    {teto_rollObjShapes, (u32)_sizeof_teto_rollObjShapes, teto_roll4Tiles, (u32)_sizeof_teto_roll4Tiles, 0, 0, 0},
    {teto_rollObjShapes, (u32)_sizeof_teto_rollObjShapes, teto_roll3Tiles, (u32)_sizeof_teto_roll3Tiles, 0, 0, 0},
    {teto_rollObjShapes, (u32)_sizeof_teto_rollObjShapes, teto_roll4Tiles, (u32)_sizeof_teto_roll4Tiles, 0, 0, 0},
};

AnimatedSprite animTeto[NUM_OF_PLAYER_ANIM] = {
    [ANIM_IDLE] = {TRUE, 1, (AnimSpriteFrame*)idleFrames},
    [ANIM_WALK] = {TRUE, 8, (AnimSpriteFrame*)walkFrames},
    [ANIM_RUN] = {TRUE, 4, (AnimSpriteFrame*)runFrames},
    [ANIM_PUSH] = {TRUE, 4, (AnimSpriteFrame*)pushFrames},
    [ANIM_ROLL] = {TRUE, 8, (AnimSpriteFrame*)rollFrames},
};

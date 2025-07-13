#include "data/include/animation_data.h"
#include "data/include/obj_shape_data.h"
#include "data/include/sprite_data.h"

static const AnimSpriteFrame idleFrames[] = {
    { teto_idleObjShapes, (u32)_sizeof_teto_idleObjShapes, teto_idleTiles, (u32)_sizeof_teto_idleTiles, -2, -4, 0},
};

static const AnimSpriteFrame walkFrames[] = {
    {teto_walk0ObjShapes, (u32)_sizeof_teto_walk0ObjShapes, teto_walk0Tiles, (u32)_sizeof_teto_walk0Tiles, -2, -4, 0},
    {teto_walk1ObjShapes, (u32)_sizeof_teto_walk1ObjShapes, teto_walk1Tiles, (u32)_sizeof_teto_walk1Tiles, -2, -4, 0},
    {teto_walk2ObjShapes, (u32)_sizeof_teto_walk2ObjShapes, teto_walk2Tiles, (u32)_sizeof_teto_walk2Tiles,  2, -4, 0},
    {teto_walk3ObjShapes, (u32)_sizeof_teto_walk3ObjShapes, teto_walk3Tiles, (u32)_sizeof_teto_walk3Tiles, -2, -4, 0},
    {teto_walk4ObjShapes, (u32)_sizeof_teto_walk4ObjShapes, teto_walk4Tiles, (u32)_sizeof_teto_walk4Tiles, -2, -4, 0},
    {teto_walk5ObjShapes, (u32)_sizeof_teto_walk5ObjShapes, teto_walk5Tiles, (u32)_sizeof_teto_walk5Tiles, -2, -4, 0},
    {teto_walk6ObjShapes, (u32)_sizeof_teto_walk6ObjShapes, teto_walk6Tiles, (u32)_sizeof_teto_walk6Tiles, -2, -4, 0},
    {teto_walk7ObjShapes, (u32)_sizeof_teto_walk7ObjShapes, teto_walk7Tiles, (u32)_sizeof_teto_walk7Tiles, -2, -4, 0},
};

static const AnimSpriteFrame runFrames[] = {
    { teto_run_0ObjShapes, (u32)_sizeof_teto_run_0ObjShapes, teto_run0Tiles, (u32)_sizeof_teto_run0Tiles, -2, 0, 0},
    { teto_run_1ObjShapes, (u32)_sizeof_teto_run_1ObjShapes, teto_run1Tiles, (u32)_sizeof_teto_run1Tiles, -2, 0, 0},
    { teto_run_2ObjShapes, (u32)_sizeof_teto_run_2ObjShapes, teto_run2Tiles, (u32)_sizeof_teto_run2Tiles, -2, 0, 0},
    { teto_run_3ObjShapes, (u32)_sizeof_teto_run_3ObjShapes, teto_run3Tiles, (u32)_sizeof_teto_run3Tiles, -2, 0, 0},
};

AnimatedSprite animTeto[NUM_OF_PLAYER_ANIM] = {
    [ANIM_IDLE] = {TRUE, 1, (AnimSpriteFrame*)idleFrames},
    [ANIM_WALK] = {TRUE, 8, (AnimSpriteFrame*)walkFrames},
    [ANIM_RUN] = {TRUE, 4, (AnimSpriteFrame*)runFrames},
};

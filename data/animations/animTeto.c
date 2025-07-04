#include "data/include/animation_data.h"
#include "data/include/sprite_obj_table.h"
#include "data/include/sprite_data.h"

//IDLE
static const AnimSpriteFrame idleFrames[] = {
    { sprObj32x48, sprObj32x48Lenght, teto_idleTiles, (u32)_sizeof_teto_idleTiles, 0},
};

//walk
static const AnimSpriteFrame walkFrames[] = {
    {sprObj32x48, sprObj32x48Lenght, teto_walk0Tiles, (u32)_sizeof_teto_walk0Tiles, 0},
    {sprObj32x48, sprObj32x48Lenght, teto_walk1Tiles, (u32)_sizeof_teto_walk1Tiles, 0},
    {sprObj40x48, sprObj40x48Lenght, teto_walk2Tiles, (u32)_sizeof_teto_walk2Tiles, 0},
    {sprObj32x48, sprObj32x48Lenght, teto_walk3Tiles, (u32)_sizeof_teto_walk3Tiles, 0},
    {sprObj32x48, sprObj32x48Lenght, teto_walk4Tiles, (u32)_sizeof_teto_walk4Tiles, 0},
    {sprObj32x48, sprObj32x48Lenght, teto_walk5Tiles, (u32)_sizeof_teto_walk5Tiles, 0},
    {sprObj32x48, sprObj32x48Lenght, teto_walk6Tiles, (u32)_sizeof_teto_walk6Tiles, 0},
    {sprObj32x48, sprObj32x48Lenght, teto_walk7Tiles, (u32)_sizeof_teto_walk7Tiles, 0},
};

//RUN
static const AnimSpriteFrame runFrames[] = {
    { sprObj32x40, sprObj32x40Lenght, teto_run0Tiles, (u32)_sizeof_teto_run0Tiles, 0},
    { sprObj32x40, sprObj32x40Lenght, teto_run1Tiles, (u32)_sizeof_teto_run1Tiles, 0},
    { sprObj32x40, sprObj32x40Lenght, teto_run2Tiles, (u32)_sizeof_teto_run2Tiles, 0},
    { sprObj32x40, sprObj32x40Lenght, teto_run3Tiles, (u32)_sizeof_teto_run3Tiles, 0},
};

//ANIMATIONS
AnimatedSprite animTeto[NUM_TETO_ANIMS] = {
    [ANIM_TETO_IDLE] = {TRUE, 1, (AnimSpriteFrame*)idleFrames},
    [ANIM_TETO_WALK] = {TRUE, 8, (AnimSpriteFrame*)walkFrames},
    [ANIM_TETO_RUN] = {TRUE, 4, (AnimSpriteFrame*)runFrames},
};

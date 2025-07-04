#include "sprite.h"
#include "gba_objects.h"

const SpriteObj sprObj32x40[] = {
    {0, 8, 0, 0, 0, OBJ_32x32},
    {0, 40, 0, 0, 16, OBJ_32x8}
};
const SpriteObj sprObj32x48[] = {
    {0, 0, 0, 0, 0, OBJ_32x32},
    {0, 32, 0, 0, 16, OBJ_32x16}
};
const SpriteObj sprObj40x48[] = {
    {0, 0, 0, 0, 0, OBJ_32x32},
    {0, 32, 0, 0, 16, OBJ_32x16},
    {32, 0, -8, 0, 24, OBJ_8x32},
    {32, 32, -8, 0, 28, OBJ_8x16}
};

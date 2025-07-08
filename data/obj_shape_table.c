#include "sprite.h"
#include "gba_objects.h"

const ObjShape objShape32x40[] = {
    {16, 20, 0,  OBJ_32x32},
    {16, 20 - 32, 16, OBJ_32x8}
};
const ObjShape objShape32x48[] = {
    {16, 24, 0,  OBJ_32x32},
    {16, 24 - 32, 16, OBJ_32x16}
};
const ObjShape objShape40x48[] = {
    {20,  24,  0,  OBJ_32x32},
    {20,  24 - 32, 16, OBJ_32x16},
    {20 - 32, 24,  24, OBJ_8x32},
    {20 - 32, 24 - 32, 28, OBJ_8x16}
};
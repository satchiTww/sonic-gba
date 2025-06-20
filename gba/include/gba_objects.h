#ifndef GBA_OBJECTS_H
#define GBA_OBJECTS_H

#include "gba_video.h"

//credits to Jasper “cearn” Vijn

typedef struct {
    u16 attr0;
    u16 attr1;
    u16 attr2;
    s16 fill;
} ALIGN4 OBJ_ATTR;

typedef struct {
    u16 fill0[3];
    s16 pa;
    u16 fill1[3];
    s16 pb;
    u16 fill2[3];
    s16 pc;
    u16 fill3[3];
    s16 pd;
} ALIGN4 OBJ_AFFINE;

#define OAM_MEM ((OBJ_ATTR*)OAM)

INLINE OBJ_ATTR *obj_set_attr(OBJ_ATTR *obj, u16 attr0, u16 attr1, u16 attr2)
{
    obj->attr0 = attr0;
    obj->attr1 = attr1;
    obj->attr2 = attr2;
    return obj;
}

INLINE void obj_set_pos(OBJ_ATTR *obj, int x, int y)
{
    obj->attr0 &= 0xFF00; obj->attr0 |= ATTR0_YPOS(y);
    obj->attr1 &= 0xFE00; obj->attr1 |= ATTR1_XPOS(x);
}

#endif
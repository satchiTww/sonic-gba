#ifndef GBA_OBJECTS_H
#define GBA_OBJECTS_H

#include "gba_video.h"

#define OAM_MAX_ENTRIES 128

typedef struct {
    //attribute 0
    u32 yPos:8;
    u32 affineMode:2;
    u32 objMode:2;
    u32 mosaic:1;
    u32 colorMode:1;
    u32 shape:2;

    //attribute 1
    u32 xPos:9;
    u32 affineIndex:3; //lower 3 bits
    u32 hFlip:1;
    u32 vFlip:1;
    u32 size:2;

    //attribute 2
    u16 tileID:10;
    u16 bgPriority:2;
    u16 paletteNum:4;

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

extern OBJ_ATTR obj_buffer[OAM_MAX_ENTRIES];

#define OBJ_AFFINE        1
#define OBJ_HIDE          2
#define OBJ_AFFINE_DOUBLE 3

#define OBJ_ALPHA_BLEND   1
#define OBJ_WINDOW        2

#define OBJ_4BPP          0
#define OBJ_8BPP          1

#define OBJ_SHAPE_SQUARE  0
#define OBJ_SHAPE_WIDE    1
#define OBJ_SHAPE_TALL    2
#define OBJ_SIZE_0        0
#define OBJ_SIZE_1        1
#define OBJ_SIZE_2        2
#define OBJ_SIZE_3        3

INLINE void obj_set_pos(OBJ_ATTR *obj, int x, int y)
{
    //obj->attr0 &= 0xFF00; obj->attr0 |= ATTR0_YPOS(y);
    //obj->attr1 &= 0xFE00; obj->attr1 |= ATTR1_XPOS(x);

    obj->xPos = x;
    obj->yPos = y;
}

#endif
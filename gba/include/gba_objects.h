#ifndef GBA_OBJECTS_H
#define GBA_OBJECTS_H

#include "gba_typedefs.h"
#include "gba_video.h"
#include "gba_dma.h"

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

extern OBJ_ATTR oam_buffer[OAM_MAX_ENTRIES];

//keeps track of all the objects currently being displayed
extern u32 gObjCount;

#define OBJ_AFFINE        1
#define OBJ_DISABLE       2
#define OBJ_AFFINE_DOUBLE 3

#define OBJ_ALPHA_BLEND   1
#define OBJ_WINDOW        2

#define OBJ_4BPP          0
#define OBJ_8BPP          1

//shapes and sizes
#define OBJ_SHAPE_SQUARE  0
#define OBJ_SHAPE_WIDE    1
#define OBJ_SHAPE_TALL    2
#define OBJ_SIZE_0        0
#define OBJ_SIZE_1        1
#define OBJ_SIZE_2        2
#define OBJ_SIZE_3        3

//shapes + sizes
#define OBJ_8x8   0x0
#define OBJ_16x16 0x1
#define OBJ_32x32 0x2
#define OBJ_64x64 0x3
#define OBJ_16x8  0x4
#define OBJ_32x8  0x5
#define OBJ_32x16 0x6
#define OBJ_64x32 0x7
#define OBJ_8x16  0x8
#define OBJ_8x32  0x9
#define OBJ_16x32 0xA
#define OBJ_32x64 0xB

//hides all the objects in oam
void obj_init_oam();

//Copy n entries in the oam buffer to the hardware OAM
INLINE void obj_update_oam(u32 objCount)
{
    if (!objCount) objCount = 1;
    dma3_cpy(OAM_MEM, oam_buffer, objCount * 2, DMA_CPY32);
}

#endif
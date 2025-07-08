#ifndef GBA_OBJECTS_H
#define GBA_OBJECTS_H

#include "gba_typedefs.h"
#include "gba_video.h"
#include "gba_dma.h"

#define OAM_MAX_ENTRIES 128

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

extern OBJ_ATTR oam_buffer[OAM_MAX_ENTRIES];

extern int obj_width_lookup[16];
extern int obj_height_lookup[16];

//Attribute 0 bits
#define ATTR0_YPOS(y)          ((y) & 0x00FF)
#define ATTR0_MODE(m)          (((m) << 8) & 0x0300)
#define ATTR0_NORMAL           0x0000
#define ATTR0_AFF              0x0100
#define ATTR0_HIDE             0x0200
#define ATTR0_AFF_DBL          0x0300
#define ATTR0_GFX(g)           (((g) << 0xA) & 0x0C00)
#define ATTR0_BLEND            0x0400
#define ATTR0_WIN              0x0800
#define ATTR0_MOSAIC           0x1000
#define ATTR0_4BPP             0x0000
#define ATTR0_8BPP             0x2000
#define ATTR0_SHAPE(s)         (((s) << 0xE) & 0xC000)
#define ATTR0_SQUARE           0x0000
#define ATTR0_WIDE             0x4000
#define ATTR0_TALL             0x8000

//Attr1 bits
#define ATTR1_XPOS(x)          ((x) & 0x01FF)
#define ATTR1_AFF_ID(i)        (((i) << 9) & 0x3E00)
#define ATTR1_FLIP(f)          (((f) << 0xC) & 0x3000)
#define ATTR1_HFLIP            0x1000
#define ATTR1_VFLIP            0x2000
#define ATTR1_SIZE(s)          (((s) << 0xE) & 0xC000)
#define ATTR1_SIZE0            0x0000
#define ATTR1_SIZE1            0x4000
#define ATTR1_SIZE2            0x8000
#define ATTR1_SIZE3            0xC000

//Attr2 bits
#define ATTR2_TILE_ID(i)       ((i) & 0x3FF)
#define ATTR2_PRIORITY(p)      (((p) << 0xA) & 0x0C00)
#define ATTR2_PAL_ID(i)        (((i) << 0xC) & 0xF000)

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

void obj_init_oam();

INLINE OBJ_ATTR *obj_set_attributes(OBJ_ATTR *obj, u16 attr0, u16 attr1, u16 attr2)
{
    obj->attr0 = attr0;
    obj->attr1 = attr1;
    obj->attr2 = attr2;

    return obj;
}

INLINE void obj_clear_oam_buffer()
{
    for (int i = 0; i < OAM_MAX_ENTRIES; i++) {
        obj_set_attributes(&oam_buffer[i], ATTR0_HIDE, 0, 0);
    }
}

INLINE void obj_update_oam()
{
    dma3_cpy(OAM_MEM, oam_buffer, OAM_MAX_ENTRIES * 2, DMA_CPY32);
    obj_clear_oam_buffer();
}

INLINE u8 obj_get_width(u8 format)
{
    return obj_width_lookup[format];
}

INLINE u8 obj_get_height(u8 format)
{
    return obj_height_lookup[format];
}

#endif
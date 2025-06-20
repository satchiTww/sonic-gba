#ifndef GBA_VIDEO_H
#define GBA_VIDEO_H

#include "gba_typedefs.h"
#include "gba_memmap.h"

#define SCREEN_WIDTH   240
#define SCREEN_HEIGHT  160

#define VIDEO_MEM ((u16*)VRAM)

/*===========COLOR=================*/
typedef u16 COLOR;

#define COLOR_BLACK   0x0000
#define COLOR_RED     0x001F
#define COLOR_GREEN   0x03E0
#define COLOR_YELLOW  0x03FF
#define COLOR_BLUE    0x7C00
#define COLOR_MAG     0x7C1F
#define COLOR_CYAN    0x7FE0
#define COLOR_WHITE   0x7FFF

INLINE COLOR RGB15(u32 red, u32 green, u32 blue)
{   return red | (green << 5) | (blue << 10);   }

/*=======REG_DISPCNT BITS============*/
//bits 0-2
#define DISPCNT_MODE_0 0x0000
#define DISPCNT_MODE_1 0x0001
#define DISPCNT_MODE_2 0x0002
#define DISPCNT_MODE_3 0x0003
#define DISPCNT_MODE_4 0x0004
#define DISPCNT_MODE_5 0x0005
//bit 3 (GBC. Read Only. Should stay at 0)
//bit 4
//bit 5
//bit 6 (1D or 2D Sprite Mode)
#define DISPCNT_1DSPRT 0x0040
//bit 7
//bits 8-B (Enable display of BG layers)
#define DISPCNT_BG0    0x0100
#define DISPCNT_BG1    0x0200
#define DISPCNT_BG2    0x0400
#define DISPCNT_BG3    0x0800
//bit C (Enable Sprites)
#define DISPCNT_OBJ    0x1000
//bit D
//bit E
//bit F
/*=========REG_DISPSTAT BITS============*/
#define DISPSTAT_VSTAT      0x0001 //0 during vdraw, 1 during vblank
#define DISPSTAT_HSTAT      0x0002 //0 during hdraw, 1 during hblank
#define DISPSTAT_VCTRG_STAT 0x0004 //Gets set to 1 when a Y trigger interrupt occurs
#define DISPSTAT_VB_IRQ     0x0008
#define DISPSTAT_HB_IRQ     0x0010
#define DISPSTAT_VCTRG_IRQ  0x0020
#define DISPSTAT_VCTRG_LINE(x) (((x) << 8) & 0xFF00)

/*=======REG_BGCNT BITS============*/
#define BGCNT_PRIORITY0       0x0000
#define BGCNT_PRIORITY1       0x0001
#define BGCNT_PRIORITY2       0x0002
#define BGCNT_PRIORITY3       0x0003
#define BGCNT_CHARBLOCK0      0x0000
#define BGCNT_CHARBLOCK1      0x0004
#define BGCNT_CHARBLOCK2      0x0008
#define BGCNT_CHARBLOCK3      0x000C
#define BGCNT_MOSAIC          0x0040
#define BGCNT_256COLOR        0x0080
#define BGCNT_SCRNBLOCK(x)    (((x) << 8) & 0x1F00)
#define BGCNT_WRAP            0x2000
#define BGCNT_SIZE0           0x0000 //256x256 | 128x128
#define BGCNT_SIZE1           0x4000 //512x256 | 256x256
#define BGCNT_SIZE2           0x8000 //256x512 | 512x512
#define BGCNT_SIZE3           0xC000 //512x512 | 1024x1024
/*===============PALETTE====================*/
#define PAL_MEM   ((u16*)PALRAM)

#define BG_PAL_INDEX 0
#define OBJ_PAL_INDEX 256

typedef struct {
    const u16 *data;
    int lenght;
    int index;
} Palette;

void load_palette(const u16* data, int lenght, int index);

/*================TILES===================*/
#define TILE_SIZE 8

#define OAM_CHARBLOCK 4

typedef struct {
    const u16* data;
    int lenght;
    int char_block;
    int char_block_index;
} Tileset;

typedef struct {
    const u16* data;
    int lenght;
    int scrn_block_index;
} Tilemap;

INLINE u16* char_block(u32 block)
{    return (u16*)(VRAM + (block*0x4000));    }


INLINE u16* screen_block(u32 block)
{    return (u16*)(VRAM + (block*0x800));    }

void load_tileset(const u16* data, int lenght, int ch_block, int index);
void load_tilemap(const u16* data, int lenght, int scrn_block);
void load_scroller_tilemap(const u16* data, int scrn_block, int stage_width, int x_grid, int y_grid);

/*===============OAM (Sprites)================*/
typedef struct {
    u16 attr0;
    u16 attr1;
    u16 attr2;
    s16 fill;
} ALIGN4 OBJ_ATTR; //credits to Jasper “cearn” Vijn

typedef struct {
    u16 fill0[3];
    s16 pa;
    u16 fill1[3];
    s16 pb;
    u16 fill2[3];
    s16 pc;
    u16 fill3[3];
    s16 pd;
} ALIGN4 OBJ_AFFINE; //credits to Jasper “cearn” Vijn

#define OAM_MEM   ((OBJATTR*)OAM)

//Attr0 bits
#define ATTR0_YPOS(y)    ((y) & 0xFF)
#define ATTR0_AFFINE     0x0200
#define ATTR0_SEMITRANS  0x0400
#define ATTR0_OBJWINDOW  0x0800
#define ATTR0_MOSAIC     0x1000
#define ATTR0_256COLOR   0x2000
#define ATTR0_SPRTSHAPE0 0x0000
#define ATTR0_SPRTSHAPE1 0x4000
#define ATTR0_SPRTSHAPE2 0x8000
#define ATTR0_SPRTSHAPE3 0xC000

//Attr1 bits
#define ATTR1_XPOS(x)          ((x) & 0x1FF)
#define ATTR1_HFLIP            0x1000
#define ATTR1_VFLIP            0x2000
#define ATTR1_ROT_SCAL_INDX(x) (((x) << 9) & 0x3E00)
#define ATTR1_SPRTSIZE0        0x0000
#define ATTR1_SPRTSIZE1        0x4000
#define ATTR1_SPRTSIZE2        0x8000
#define ATTR1_SPRTSIZE3        0xC000

//Attr2 bits
#define ATTR2_TILENUM(x) ((x) & 0x3FF)
#define ATTR2_PRIORITY0  0x0000
#define ATTR2_PRIORITY1  0x0400
#define ATTR2_PRIORITY2  0x0800
#define ATTR2_PRIORITY3  0x0C00
#define ATTR2_PALNUM(x)  (((x) << 12) & 0xF000)

//Attr3 bits (sprite rotation and scaling)
#define AFFINE3_ROTSCAL(s, i, f) (((s) << 16) & 0x8000) | (((i) << 8) & 0x7F00) | ((f) & 0xFF) //sign, integer, fraction

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
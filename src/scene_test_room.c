#include "scene.h"
#include "gba.h"
#include "stage.h"
#include "data/backgrounds/TZ_bg0.h"
#include "data/tilemaps/TestZone.h"

static Stage testZone=
{
    .tilemap = TestZoneMap,
    .mapWidth = 1008,
    .mapHeight = 224
};

void move_bg0();

static void test_room_init()
{
    REG_DISPCNT =
        DISPCNT_MODE_0 |
        DISPCNT_BG0    |
        DISPCNT_BG1    |
        DISPCNT_OBJ    |
        DISPCNT_1DSPRT
    ;

    /*Background 0 Setup*/
    REG_BG0CNT =
        BGCNT_PRIORITY3     |
        BGCNT_CHARBLOCK0    |
        BGCNT_SCRNBLOCK(28) |
        BGCNT_SIZE0
    ;
    load_palette(TZ_bg0Pal, TZ_bg0PalLen, 0);
    load_tileset(TZ_bg0Tiles, TZ_bg0TilesLen, 0, 0);
    load_tilemap(TZ_bg0Map, TZ_bg0MapLen, 28);

    /*Background 1 Setup*/
    REG_BG1CNT =
        BGCNT_PRIORITY2     |
        BGCNT_CHARBLOCK0    |
        BGCNT_SCRNBLOCK(29) |
        BGCNT_SIZE0
    ;
    load_palette(TestZonePal, TestZonePalLen, 2);
    load_tileset(TestZoneTiles, TestZoneTilesLen, 0, 2);
}

static void test_room_update()
{
    move_bg0();

    //scroll bg1 (tilemap)
    load_scroller_tilemap(testZone.tilemap, 29, testZone.mapWidth, 0, 8);
}

static void test_room_leave()
{

}

Scene testRoom=
{
    .init = test_room_init,
    .update = test_room_update,
    .leave = test_room_leave
};

void move_bg0()
{
    static fixed8 bg0HScroll = 0;
    static fixed8 bg0VScroll = 0;

    //move BG0
    bg0HScroll += FIXED8(0, 32);
    bg0VScroll += FIXED8(0, 32);
    REG_BG0HOFS = fixed8_to_int(bg0HScroll);
    REG_BG0VOFS = fixed8_to_int(bg0VScroll);
}
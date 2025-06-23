#include "gba.h"
#include "scene.h"
#include "stage.h"
#include "camera.h"
#include "player.h"
#include "sprite_teto.h"
#include "data/backgrounds/TZ_bg0.h"
#include "data/tilemaps/TestZone.h"

static Stage testZone=
{
    .tilemap_data = TestZoneMap,
    .mapWidth = 1008,
    .mapHeight = 224
};

static Camera *camera;

static Player *player;

static void move_bg0();
static void move_bg1();

static void test_room_init()
{
    //Display setup
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

    /*oam setup*/
    load_sprite(&sprTeto, 0, 0, 12, 0);
    
    camera = camera_create(camera, 0, 64);
    player = player_create(player, FIXED8(48, 0), FIXED8(128, 0), AIRBORNE);
}

static void test_room_update()
{
    player_routine(player, &testZone, camera);

    camera_clamp(camera, 0, testZone.mapWidth - SCREEN_WIDTH, 0, testZone.mapHeight - SCREEN_HEIGHT);

    sprite_set_pos(
        &sprTeto,
        (fixed8_to_int(player->xPos) - camera->xPos) - PLAYER_SPRITE_OFFSET_X,
        (fixed8_to_int(player->yPos) - camera->yPos) - PLAYER_SPRITE_OFFSET_Y
    );

    move_bg0();
    move_bg1();

    obj_update_oam();
}

static void test_room_leave()
{
    camera_destroy(camera);
    player_destroy(player);
}

Scene testRoom=
{
    .init = test_room_init,
    .update = test_room_update,
    .leave = test_room_leave
};

static void move_bg0()
{
    static fixed8 bg0HScroll = 0;
    static fixed8 bg0VScroll = 0;

    //move BG0
    bg0HScroll += FIXED8(0, 32);
    bg0VScroll += FIXED8(0, 32);
    REG_BG0HOFS = fixed8_to_int(bg0HScroll);
    REG_BG0VOFS = fixed8_to_int(bg0VScroll);
}

static void move_bg1()
{
    static fixed8 bg1HScroll = 0;
    static fixed8 bg1VScroll = 0;

    bg1HScroll = camera->xPos % TILE_SIZE;
    bg1VScroll = camera->yPos % TILE_SIZE;
    REG_BG1HOFS = bg1HScroll;
    REG_BG1VOFS = bg1VScroll;

    load_scroller_tilemap(
        testZone.tilemap_data,
        29,
        testZone.mapWidth,
        camera->xPos / TILE_SIZE,
        camera->yPos / TILE_SIZE
    );
}
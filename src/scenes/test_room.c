#include "gba.h"
#include "math_func.h"
#include "scenes.h"
#include "camera.h"
#include "player.h"
#include "data/include/bg_data.h"
#include "data/include/level_layout.h"
#include "sprite.h"

#define TEST_ROOM_WIDTH  1008
#define TEST_ROOM_HEIGHT 224

static Camera *camera;
static Player *player;

static void move_bg0(void);
static void move_bg1(void);

static struct SpriteListNode *spriteNode;

static void test_room_init(void)
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
    palette_load(bg0Pal, (u32)_sizeof_bg0Pal, 0);
    tiles_load(bg0Tiles, (u32)_sizeof_bg0Tiles, 0, 0);
    tiles_load_tilemap(bg0Map, (u32)_sizeof_bg0Map, 28);

    /*Background 1 Setup*/
    REG_BG1CNT =
        BGCNT_PRIORITY2     |
        BGCNT_CHARBLOCK0    |
        BGCNT_SCRNBLOCK(29) |
        BGCNT_SIZE0
    ;
    palette_load(test_zone_layoutPal, (u32)_sizeof_test_zone_layoutPal, 2);
    tiles_load(test_zone_layoutTiles, (u32)_sizeof_test_zone_layoutTiles, 0, 2);

    obj_init_oam();

    camera = camera_create(0, FIXED8(64, 0), FIXED8(TEST_ROOM_WIDTH, 0), FIXED8(TEST_ROOM_HEIGHT, 0));
    player = player_create(FIXED8(48, 0), FIXED8(188, 0), STATE_NORMAL, CHAR_TETO, &spriteNode);
}

static void test_room_update(void)
{
    player_routine(player, camera);

    camera_update_position(camera);

    player_render(player, camera);

    move_bg1();
    move_bg0();

    sprite_add_list_to_oam_buffer(spriteNode);
    obj_update_oam();
}

static void test_room_leave(void)
{
    camera_destroy(camera);
    player_destroy(player);
}



static void move_bg0(void)
{
    static fixed8 bg0HScroll = 0;
    static fixed8 bg0VScroll = 0;

    //move BG0
    bg0HScroll += FIXED8(0, 32);
    bg0VScroll += FIXED8(0, 32);
    REG_BG0HOFS = fixed8_to_int(bg0HScroll);
    REG_BG0VOFS = fixed8_to_int(bg0VScroll);
}

static void move_bg1(void)
{
    static int bg1HScroll = 0;
    static int bg1VScroll = 0;
    int camX = fixed8_to_int(camera->xPos);
    int camY = fixed8_to_int(camera->yPos);

    bg1HScroll = camX % TILE_SIZE;
    bg1VScroll = camY % TILE_SIZE;
    REG_BG1HOFS = bg1HScroll;
    REG_BG1VOFS = bg1VScroll;

    tiles_tilemap_scroll(
        test_zone_layoutMap,
        29,
        TEST_ROOM_WIDTH / TILE_SIZE,
        camX / TILE_SIZE,
        camY / TILE_SIZE
    );
}

Scene testRoom = {
    .init = test_room_init,
    .update = test_room_update,
    .leave = test_room_leave
};
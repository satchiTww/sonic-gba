#include "scenes.h"
#include "gba.h"
#include "sprite.h"
#include "math_func.h"
#include "data/include/bg_data.h"
#include "data/include/sprite_data.h"
#include "data/include/animation_data.h"

static struct SpriteListNode *spriteNode;

static Sprite *tetoSprite;

u8 angle = 0;

int isHflip = 0;

static void sprite_room_init(void)
{
   palette_load(bg0Pal, (u32)_sizeof_bg0Pal, 0);

   obj_init_oam();

   palette_load(teto_pal, (u32)_sizeof_teto_pal, PAL_OAM_INDEX);

   tetoSprite = sprite_init(&spriteNode, 120, 80, 0, 0, 0, 0);
   sprite_set_animation(tetoSprite, &animTeto[1]);
}

static void sprite_room_update(void)
{
    if (key_hit(KEY_SELECT)) {
        if (tetoSprite->isAffine)
            tetoSprite->isAffine = FALSE;
        else {
            tetoSprite->isAffine = TRUE;
        }
    }

    if (key_is_down(KEY_RIGHT)) {
        isHflip = 0;
    }
    if (key_is_down(KEY_LEFT)) {
        isHflip = 1;
    }

    if (key_is_down(KEY_R)) {
        angle++;
    }
    if (key_is_down(KEY_L)) {
        angle--;
    }

    sprite_set_rotation(tetoSprite, angle);

    sprite_render_animation(tetoSprite, 4);
    sprite_add_list_to_oam_buffer(spriteNode);
    obj_update_oam();
}

static void sprite_room_leave(void)
{
    
}

Scene spriteRoom = {
    .init = sprite_room_init,
    .update = sprite_room_update,
    .leave = sprite_room_leave
};
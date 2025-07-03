#include "sprite.h"
#include "gba_tiles.h"
#include "gba_objects.h"
#include <stdlib.h>

/*return a OBJ_ATTR with the attributes defined by the sprite object on
  the index defined in "sprObjIndex"*/
static OBJ_ATTR sprite_get_object(Sprite *sprite, u32 sprObjIndex);

Sprite *sprite_create(
    struct SpriteListNode **spriteNode,
    u16 xPos,
    u16 yPos,
    u16 tileID,
    u16 palNum,
    u8 bgPriority,
    u8 spritePriority,
    u8 numOfObjs,
    SpriteObj *sprObj
)
{
    Sprite *spr = malloc(sizeof(Sprite));

    spr->xPos = xPos;
    spr->yPos = yPos;
    spr->currentAnim = NULL;
    spr->isActive = TRUE;
    spr->hFlip = FALSE;
    spr->vFlip = FALSE;
    spr->tileID = tileID;
    spr->paletteNum = palNum;
    spr->bgPriority = bgPriority;
    spr->spritePriority = spritePriority;
    spr->numOfObjs = numOfObjs;
    spr->sprObj = sprObj;

    *spriteNode = sprite_add_to_list(*spriteNode, spr);

    return spr;
}

struct SpriteListNode *sprite_add_to_list(struct SpriteListNode *head, Sprite *sprite)
{
    struct SpriteListNode *newNode = (struct SpriteListNode*)malloc(sizeof(struct SpriteListNode));

    newNode->spritePtr = sprite;
    newNode->next = NULL;

    if (head == NULL || newNode->spritePtr->spritePriority < head->spritePtr->spritePriority) {
        newNode->next = head;
        return newNode;
    }
    
    struct SpriteListNode *prev = head;
    struct SpriteListNode *curr = head->next;

    while (curr != NULL && curr->spritePtr->spritePriority <= sprite->spritePriority) {
        prev = curr;
        curr = curr->next;
    }

    newNode->next = curr;
    prev->next = newNode;

    return head;
}

struct SpriteListNode *sprite_remove_from_list(struct SpriteListNode *head, Sprite *sprite)
{
    struct SpriteListNode *curr = head;
    struct SpriteListNode *prev = NULL;

    if (curr != NULL && curr->spritePtr == sprite) {
        head = curr->next;
        free (curr);
        return head;
    }

    while (curr != NULL && curr->spritePtr != sprite) {
        prev = curr;
        curr = curr->next;
    }

    if (curr == NULL)
        return head;
    
    prev->next = curr->next;

    free(curr);
    return head;
}

void sprite_add_list_to_oam_buffer(struct SpriteListNode *head)
{
    u32 objCount = 0;
    while (head != NULL) {
        if (head->spritePtr->isActive) {
            for (u32 j = 0; j < head->spritePtr->numOfObjs; objCount++, j++) {
                OBJ_ATTR obj = sprite_get_object(head->spritePtr, j);
                oam_buffer[objCount] = obj;
            }
        }
        head = head->next;
    }
}

void sprite_render_animation(Sprite *sprite, u32 duration)
{
    if (sprite->currentAnim == NULL) return;
    
    AnimatedSprite *anim = sprite->currentAnim;

    animation_update_frame(anim, duration);

    u32 index = anim->animIndex;

    tiles_load(
        anim->tileData[index].data,
        anim->tileData[index].size,
        TILE_OAM_CHARBLOCK,
        sprite->tileID
    );

    sprite_load_sprite_obj(
        sprite,
        anim->sprObjData[index].data,
        anim->sprObjData[index].size
    );
}

OBJ_ATTR sprite_get_object(Sprite *sprite, u32 sprObjIndex)
{
    OBJ_ATTR obj;
    u16 attr0 =
        ATTR0_YPOS(sprite->yPos + sprite->sprObj[sprObjIndex].offsetY) +
        ATTR0_SHAPE((sprite->sprObj[sprObjIndex].format & 0xC) >> 2)
    ;
    u16 attr1 =
        ATTR1_XPOS(sprite->xPos + sprite->sprObj[sprObjIndex].offsetX) +
        ATTR1_FLIP(sprite->hFlip | sprite->vFlip) +
        ATTR1_SIZE(sprite->sprObj[sprObjIndex].format & 0x3)
    ;
    u16 attr2 =
        ATTR2_TILE_ID(sprite->tileID + sprite->sprObj[sprObjIndex].offsetTileID) +
        ATTR2_PRIORITY(sprite->bgPriority) +
        ATTR2_PAL_ID(sprite->paletteNum)
    ;

    obj_set_attributes(&obj, attr0, attr1, attr2);

    return obj;
}
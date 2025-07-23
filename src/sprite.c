#include "sprite.h"
#include "gba_tiles.h"
#include "gba_objects.h"
#include <stdlib.h>

/*return a OBJ_ATTR with the attributes defined by the sprite object on
  the index defined in "objShapeIndex"*/
static OBJ_ATTR sprite_get_object(const Sprite *sprite, u32 objShapeIndex);

Sprite *sprite_init(
    struct SpriteListNode **spriteNode,
    u16 xPos,
    u16 yPos,
    u16 tileID,
    u16 palNum,
    u8 bgPriority,
    u8 spritePriority
)
{
    Sprite *spr = malloc(sizeof(Sprite));

    spr->xPos = xPos;
    spr->yPos = yPos;
    spr->xOffset = 0;
    spr->yOffset = 0;
    spr->currentAnim = NULL;
    spr->aff = (SpriteAffParam){0, 0, 0, 0};
    spr->animTimer = 0;
    spr->animIndex = 0;
    spr->isActive = TRUE;
    spr->affineID = 0;
    spr->isAffine = FALSE;
    spr->hFlip = FALSE;
    spr->vFlip = FALSE;
    spr->tileID = tileID;
    spr->paletteNum = palNum;
    spr->bgPriority = bgPriority;
    spr->spritePriority = spritePriority;
    spr->numOfObjs = 1;
    spr->objShape = &(ObjShape){0, 0, 0, 0};

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
        Sprite *currSprite = head->spritePtr;
        
        if (currSprite->isActive) {
            for (u32 j = 0; j < currSprite->numOfObjs; j++) {

                OBJ_ATTR obj = sprite_get_object(currSprite, j);

                oam_buffer[objCount] = obj;

                if (currSprite->isAffine) {

                    obj_set_aff_attr(
                        &oam_aff_buffer[currSprite->affineID],
                        currSprite->aff.pa,
                        currSprite->aff.pb,
                        currSprite->aff.pc,
                        currSprite->aff.pd
                    );
                }

                objCount++;
            }
        }

        head = head->next;
    }
}

void sprite_render_animation(Sprite *sprite, u32 duration)
{
    if (sprite->currentAnim == NULL) return;

    animation_update_frame(sprite->currentAnim, duration, &sprite->animTimer, &sprite->animIndex);

    AnimSpriteFrame currFrame = sprite->currentAnim->frames[sprite->animIndex];

    sprite_load_obj_shape(
        sprite,
        currFrame.ObjShapeData,
        currFrame.ObjShapeDataLenght >> 3
    );

    tiles_load(
        currFrame.tileData,
        currFrame.tileDataLenght,
        TILE_OAM_CHARBLOCK,
        sprite->tileID
    );

    sprite->xOffset = sprite->hFlip ? -currFrame.offsetX : currFrame.offsetX;
    sprite->yOffset = sprite->vFlip ? -currFrame.offsetY : currFrame.offsetY;
}

OBJ_ATTR sprite_get_object(const Sprite *sprite, u32 objShapeIndex)
{
    OBJ_ATTR obj;

    ObjShape objShape = sprite->objShape[objShapeIndex];

    int objOffX = sprite->hFlip ? obj_get_width(objShape.format)  - objShape.offsetX : objShape.offsetX;
    int objOffY = sprite->vFlip ? obj_get_height(objShape.format) - objShape.offsetY : objShape.offsetY;

    u16 attr0 =
        ATTR0_YPOS(sprite->yPos + sprite->yOffset - objOffY) +
        ATTR0_SHAPE((objShape.format & 0xC) >> 2) +
        (sprite->isAffine * ATTR0_AFF)
    ;

    u16 attr1 =
        ATTR1_XPOS(sprite->xPos + sprite->xOffset - objOffX) +
        ATTR1_FLIP(sprite->hFlip | (sprite->vFlip << 1) ) * (!sprite->isAffine) +
        ATTR1_SIZE(objShape.format & 0x3) +
        ATTR1_AFF_ID(sprite->affineID) //todo: things
    ;
    
    u16 attr2 =
        ATTR2_TILE_ID(sprite->tileID + objShape.offsetTileID) +
        ATTR2_PRIORITY(sprite->bgPriority) +
        ATTR2_PAL_ID(sprite->paletteNum)
    ;

    obj_set_attributes(&obj, attr0, attr1, attr2);

    return obj;
}
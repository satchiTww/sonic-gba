#include "sprite.h"
#include <stdlib.h>

Sprite *sprite_create(struct SpriteListNode **spriteNode, u32 xPos, u32 yPos, u16 tileID, u16 palNum, u16 bgPriority, u32 spritePriority, u32 objCount)
{
    Sprite *spr = calloc(1, sizeof(Sprite));

    spr->xPos = xPos;
    spr->yPos = yPos;
    spr->tileID = tileID;
    spr->paletteNum = palNum;
    spr->bgPriority = bgPriority;
    spr->spritePriority = spritePriority;
    spr->numOfObjs = objCount;

    SpriteObj *sprObj = calloc(objCount, sizeof(SpriteObj));
    spr->sprObj = sprObj;

    *spriteNode = sprite_add_to_list(*spriteNode, spr);

    return spr;
}

void sprite_add_list_to_oam_buffer(struct SpriteListNode *head)
{
    gObjCount = 0;
    while (head != NULL) {
        for (u32 i = 0; i < head->spritePtr->numOfObjs; gObjCount++, i++) {
            OBJ_ATTR obj = sprite_get_object(head->spritePtr, i);
            oam_buffer[gObjCount] = obj;
        }
        head = head->next;
    }
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

OBJ_ATTR sprite_get_object(Sprite *sprite, u32 objectNum)
{
    OBJ_ATTR obj = {
        .xPos = sprite->xPos + sprite->sprObj[objectNum].offsetX,
        .yPos = sprite->yPos + sprite->sprObj[objectNum].offsetY,
        .hFlip = sprite->hFlip,
        .vFlip = sprite->vFlip,
        .bgPriority = sprite->bgPriority,
        .paletteNum = sprite->paletteNum,
        .tileID = sprite->tileID + sprite->sprObj[objectNum].offsetTileID,
        .shape = (sprite->sprObj[objectNum].format & 0xC) >> 2,
        .size = sprite->sprObj[objectNum].format & 0x3
    };

    return obj;
}

/*
void sprite_update(Sprite *sprite)
{
    for (u32 i = 0; i < sprite->numOfObjs; i++) {
        OBJ_ATTR obj = {
            .xPos = sprite->xPos + sprite->sprObj[i].offsetX,
            .yPos = sprite->yPos + sprite->sprObj[i].offsetY,
            .hFlip = sprite->hFlip,
            .vFlip = sprite->vFlip,
            .bgPriority = sprite->bgPriority,
            .paletteNum = sprite->paletteNum,
            .tileID = sprite->tileID + sprite->sprObj[i].offsetTileID,
            .shape = (sprite->sprObj[i].format & 0xC) >> 2,
            .size = sprite->sprObj[i].format & 0x3
        };
        oam_buffer[sprite->spritePriority + i] = obj;
    }
}
*/
/*
void sprite_load_pal(Sprite *sprite)
{
    palette_load(sprite->palette.data, sprite->palette.lenght, sprite->palette.index);
}

void sprite_set_pos(Sprite *sprite, int xPos, int yPos)
{
    sprite->xPos = xPos;
    sprite->yPos = yPos;

    for (int i = 0; i < sprite->objCount; i++) {
        obj_set_pos(
            &sprite->obj[i].attributes,
            sprite->xPos + sprite->obj[i].offsetX,
            sprite->yPos + sprite->obj[i].offsetY
        );

        obj_buffer[sprite->spritePriority + i] = sprite->obj[i].attributes;
    }
}
*/
#include "sprite.h"
#include <stdlib.h>

Sprite *sprite_create(struct SpriteListNode **spriteNode, u32 xPos, u32 yPos, u16 tileID, u16 palNum, u16 bgPriority, u32 spritePriority, u32 numOfObjs)
{
    Sprite *spr = calloc(1, sizeof(Sprite));

    spr->xPos = xPos;
    spr->yPos = yPos;
    spr->tileID = tileID;
    spr->paletteNum = palNum;
    spr->bgPriority = bgPriority;
    spr->spritePriority = spritePriority;
    spr->numOfObjs = numOfObjs;

    SpriteObj *sprObj = calloc(numOfObjs, sizeof(SpriteObj));
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

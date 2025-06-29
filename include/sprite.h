#ifndef SPRITE_H
#define SPRITE_H

#include "gba_typedefs.h"
#include "gba_objects.h"

//TODO: Affine Sprites

//struct for a object that makes a sprite
typedef struct {
    int offsetX;
    int offsetY;
    u32 offsetTileID;
    u32 format:4; //size + shape of the object
} SpriteObj;

typedef struct {
    u32 xPos;
    u32 yPos;
    u32 hFlip;
    u32 vFlip;
    u32 spritePriority; //aka oam ID 0 - 128
    u16 bgPriority;
    u16 paletteNum;
    u16 tileID;
    u32 numOfObjs;
    SpriteObj *sprObj;
} Sprite;

struct SpriteListNode {
    Sprite *spritePtr;
    struct SpriteListNode *next;
};

Sprite *sprite_create(
    struct SpriteListNode **spriteNode,
    u32 xPos, u32 yPos,
    u16 tileID,
    u16 palNum,
    u16 bgPriority,
    u32 spritePriority,
    u32 numOfObjs
);
struct SpriteListNode *sprite_add_to_list(struct SpriteListNode *head, Sprite *sprite);
void sprite_add_list_to_oam_buffer(struct SpriteListNode *head);
OBJ_ATTR sprite_get_object(Sprite *sprite, u32 objectNum);

#endif
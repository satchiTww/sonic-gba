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

//struct for the sprite
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

//struct for the sprite node. this deals with object priority in oam and other things
struct SpriteListNode {
    Sprite *spritePtr;
    struct SpriteListNode *next;
};

/*Allocates memory for a sprite and for all its objects, 
  define its main member variables and add it to the given "spriteNode" variable,
  in the order defined by the sprite's "spritePriority" variable.*/
Sprite *sprite_create(
    struct SpriteListNode **spriteNode,
    u32 xPos, u32 yPos,
    u16 tileID,
    u16 palNum,
    u16 bgPriority,
    u32 spritePriority,
    u32 numOfObjs
);

/*Allocates memory for a new sprite node and adds it in the sprite list
  in the order defined by the sprite's "spritePriority" variable.*/
struct SpriteListNode *sprite_add_to_list(struct SpriteListNode *head, Sprite *sprite);

/*Adds all objects of each sprite in the sprite list node to the oam buffer*/
void sprite_add_list_to_oam_buffer(struct SpriteListNode *head);

/*return a OBJ_ATTR with the attributes defined by the sprite object on
  the index defined in "objectNum"*/
OBJ_ATTR sprite_get_object(Sprite *sprite, u32 objectNum);

#endif
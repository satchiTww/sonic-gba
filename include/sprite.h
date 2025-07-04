#ifndef SPRITE_H
#define SPRITE_H

#include "gba_typedefs.h"
#include "animation.h"

//TODO: Affine Sprites

//struct for a object that makes a sprite
typedef struct {
    s32 offsetX;
    s32 offsetY;
    s32 hFlipOffsetX;
    s32 vFlipOffsetX;
    u16 offsetTileID;
    u8 format; //size + shape of the object
} ALIGN4 SpriteObj;

//struct for the sprite
typedef struct {
    u16 xPos;
    u16 yPos;
    AnimatedSprite *currentAnim;
    u16 animTimer;
    u16 animIndex;
    u8 isActive;
    u8 hFlip;
    u8 vFlip;
    u8 spritePriority;
    u8 bgPriority;
    u8 numOfObjs;
    u16 paletteNum;
    u16 tileID;
    SpriteObj *sprObj;
} ALIGN4 Sprite;

//struct for the sprite linked list
struct SpriteListNode {
    Sprite *spritePtr;
    struct SpriteListNode *next;
};

//globals
extern struct SpriteListNode *gSpriteNode;

/*======================FUNCTIONS=============================*/
/*Allocates memory for a sprite and for all its objects, 
  define its main member variables and add it to the given "spriteNode" variable,
  in the order defined by the sprite's "spritePriority" variable.*/
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
);

/*Allocates memory for a new sprite node and adds it in the sprite list
  in the order defined by the sprite's "spritePriority" variable.*/
struct SpriteListNode *sprite_add_to_list(struct SpriteListNode *head, Sprite *sprite);

struct SpriteListNode *sprite_remove_from_list(struct SpriteListNode *head, Sprite *sprite);

/*Adds all objects of each sprite in the sprite list node to the oam buffer*/
void sprite_add_list_to_oam_buffer(struct SpriteListNode *head);

void sprite_render_animation(Sprite *sprite, u32 duration);

INLINE void sprite_set_animation(Sprite *sprite, AnimatedSprite *newAnim)
{
    if (sprite->currentAnim == newAnim) return;

    sprite->currentAnim = newAnim;
    sprite->animTimer = 0;
    sprite->animIndex = 0;
}

INLINE void sprite_load_sprite_obj(Sprite *sprite, const SpriteObj *sprObj_data, u32 sprObj_count)
{
    sprite->numOfObjs = sprObj_count;
    sprite->sprObj = (SpriteObj*)sprObj_data;
}

#endif
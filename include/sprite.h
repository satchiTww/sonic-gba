#ifndef SPRITE_H
#define SPRITE_H

#include "gba_typedefs.h"
#include "gba_objects.h"
#include "animation.h"
#include "math_func.h"

//TODO: Affine Sprites

//struct for a object that makes a sprite
typedef struct {
    s16 offsetX;
    s16 offsetY;
    u16 offsetTileID;
    u16 format; //size + shape of the object
} ObjShape;

typedef struct {
    s16 pa;
    s16 pb;
    s16 pc;
    s16 pd;
} SpriteAffParam;

//struct for the sprite
typedef struct {
    
    u16 xPos;
    u16 yPos;

    u16 xOffset;
    u16 yOffset;

    SpriteAffParam aff;

    AnimatedSprite *currentAnim;
    u32 animTimer;
    u16 animIndex;

    u8 isActive;

    u8 isAffine;
    u8 affineID;

    u8 hFlip;
    u8 vFlip;

    u8 spritePriority;
    u8 bgPriority;

    u8 numOfObjs;

    u16 paletteNum;
    u16 tileID;

    ObjShape *objShape;

} Sprite;

//struct for the sprite linked list
struct SpriteListNode {
    Sprite *spritePtr;
    struct SpriteListNode *next;
};

/*======================FUNCTIONS=============================*/
/*Allocates memory for a sprite and for all its objects, 
  define its main member variables and add it to the given "spriteNode" variable,
  in the order defined by the sprite's "spritePriority" variable.*/
Sprite *sprite_init(
    struct SpriteListNode **spriteNode,
    u16 xPos,
    u16 yPos,
    u16 tileID,
    u16 palNum,
    u8 bgPriority,
    u8 spritePriority
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

INLINE void sprite_load_obj_shape(Sprite *sprite, const ObjShape *objShapeData, u32 obj_count)
{
    sprite->numOfObjs = obj_count;
    sprite->objShape = (ObjShape*)objShapeData;
}

INLINE void sprite_set_rotation(Sprite *sprite, u8 angle)
{
    if (!sprite->isAffine) return;

    sprite->aff.pa = angle_get_cos(angle) * (!sprite->hFlip ? 1 : -1);
    sprite->aff.pb = angle_get_sin(angle) * (!sprite->hFlip ? 1 : -1);
    sprite->aff.pc = -angle_get_sin(angle);
    sprite->aff.pd = angle_get_cos(angle);
}

#endif
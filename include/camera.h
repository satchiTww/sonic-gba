#ifndef CAMERA_H
#define CAMERA_H

#include "math_func.h"

typedef struct {
    fixed8 xPos, yPos; //top left corner
    fixed8 xSpeed, ySpeed;
    fixed8 minHorizBorder, minVertBorder;
    fixed8 maxHorizBorder, maxVertBorder;
} Camera;


Camera *camera_create(fixed8 xPos, fixed8 yPos, fixed8 maxHorizBorder, fixed8 maxVertBorder);
void camera_follow_target(Camera *camera, fixed8 targetXpos, fixed8 targetYpos);
void camera_update_position(Camera *camera);
void camera_destroy(Camera *camera);
#endif
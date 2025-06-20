#ifndef CAMERA_H
#define CAMERA_H

typedef struct {
    int xPos, yPos;
} Camera;


Camera *camera_create(Camera *camera, int xPos, int yPos);
void camera_follow(Camera *camera, int targetX, int targetY);
void camera_clamp(Camera *camera, int minX, int maxX, int minY, int maxY);
void camera_destroy(Camera *camera);
#endif
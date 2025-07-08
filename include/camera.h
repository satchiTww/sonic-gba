#ifndef CAMERA_H
#define CAMERA_H

typedef struct {
    int xPos, yPos;
} Camera;


Camera *camera_create(int xPos, int yPos);
void camera_follow_target(
    Camera* camera, 
    int targetXpos, 
    int targetYpos, 
    int leftBorder, 
    int rightBorder, 
    int topBorder,
    int bottomBorder
);
void camera_clamp(Camera *camera, int minX, int maxX, int minY, int maxY);
void camera_destroy(Camera *camera);
#endif
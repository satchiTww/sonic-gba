#include "gba_video.h"
#include "camera.h"
#include <stdlib.h>

Camera *camera_create(int xPos, int yPos)
{
    Camera *camera;

    camera = (Camera *)calloc(1, sizeof(Camera));

    camera->xPos = xPos;
    camera->yPos = yPos;

    return camera;
}

void camera_follow_target(Camera *camera, int targetX, int targetY)
{
    camera->xPos = targetX - SCREEN_WIDTH / 2;
    camera->yPos = targetY - SCREEN_HEIGHT / 2;
}

//clamp the camera position to a minimum x and y position and a maximum x and y position
void camera_clamp(Camera *camera, int minX, int maxX, int minY, int maxY)
{
    if (camera->xPos < minX)
        camera->xPos = minX;
    if (camera->xPos > maxX)
        camera->xPos = maxX;
    if (camera->yPos < minY)
        camera->yPos = minY;
    if (camera->yPos > maxY)
        camera->yPos = maxY;
}

void camera_destroy(Camera *camera)
{
    free(camera);
    camera = NULL;
}
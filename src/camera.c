#include "gba_video.h"
#include "camera.h"
#include <stdlib.h>

static fixed8 cameraHorizMaxSpeed = FIXED8(16, 0);

Camera *camera_create(fixed8 xPos, fixed8 yPos, fixed8 maxHorizBorder, fixed8 maxVertBorder)
{
    Camera *camera;

    camera = (Camera *)malloc(sizeof(Camera));

    camera->xPos = xPos;
    camera->yPos = yPos;
    camera->xSpeed = 0;
    camera->ySpeed = 0;
    camera->minHorizBorder = 0;
    camera->minVertBorder = 0;
    camera->maxHorizBorder = maxHorizBorder;
    camera->maxVertBorder = maxVertBorder;

    return camera;
}

void camera_follow_target(Camera *camera, fixed8 targetXpos, fixed8 targetYpos)
{
    fixed8 cameraCenterX = camera->xPos + FIXED8(SCREEN_WIDTH / 2, 0);
    fixed8 cameraCenterY = camera->yPos + FIXED8(SCREEN_HEIGHT / 2, 0);

    camera->xSpeed = targetXpos - cameraCenterX;
    camera->ySpeed = targetYpos - cameraCenterY;
}

void camera_update_position(Camera *camera)
{
    fixed8 camBottomLeftX;
    fixed8 camBottomLeftY;

    if (mf_abs(camera->xSpeed) > cameraHorizMaxSpeed)
        camera->xSpeed = cameraHorizMaxSpeed * mf_sign(camera->xSpeed);

    camera->xPos += camera->xSpeed;
    camera->yPos += camera->ySpeed;

    camBottomLeftX = camera->xPos + FIXED8(SCREEN_WIDTH, 0);
    camBottomLeftY = camera->yPos + FIXED8(SCREEN_HEIGHT, 0);

    if (camera->xPos < camera->minHorizBorder) {
        camera->xPos += camera->minHorizBorder - camera->xPos;
    }
    else if (camBottomLeftX > camera->maxHorizBorder) {
        camera->xPos -= camBottomLeftX - camera->maxHorizBorder;
    }

    if (camera->yPos < camera->minVertBorder) {
        camera->yPos += camera->minVertBorder - camera->yPos;
    }
    else if (camBottomLeftY > camera->maxVertBorder) {
        camera->yPos -= camBottomLeftY - camera->maxVertBorder;
    }
}

void camera_destroy(Camera *camera)
{
    free(camera);
    camera = NULL;
}
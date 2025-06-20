#ifndef SCENE_H
#define SCENE_H

typedef struct {
    void (*init)(void);
    void (*update)(void);
    void (*leave)(void);
} Scene;

#define MAX_SCENES 100 //temp value

void scene_add(Scene *scene);
void scenes_handle();
void scene_set_next(Scene *scene);

#include "scene_testRoom.h"

#endif
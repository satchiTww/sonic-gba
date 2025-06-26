#include "scenes.h"
#include <stddef.h>

static Scene *scenes[MAX_SCENES] = {0};
static Scene *current_scene;
static Scene *next_scene;

//Adds a scene to the game's registry
void scene_add(Scene *scene)
{
    for (int i = 0; i < MAX_SCENES; i++) {
        if (scenes[i] == 0) {
            scenes[i] = scene;
            return;
        }
    }
}

//Requests a change to a new scene
void scene_set_next(Scene *scene)
{
    next_scene = scene;
}

//Main scene handler, call this once per frame
void scenes_handle()
{
    if (next_scene != NULL) {
        if (current_scene != NULL && current_scene->leave != NULL)
            current_scene->leave()
        ;

        current_scene = next_scene;
        next_scene = NULL;

        if (current_scene != NULL && current_scene->init != NULL)
            current_scene->init()
        ;
    }

    if (current_scene != NULL && current_scene->update != NULL)
        current_scene->update()
    ;
}
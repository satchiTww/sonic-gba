#ifndef SCENES_H
#define SCENES_H

typedef struct {
    void (*init)(void);
    void (*update)(void);
    void (*leave)(void);
} Scene;

#define MAX_SCENES 32 //temp value

extern Scene testRoom;
extern Scene spriteRoom;

void scene_add(Scene *scene);
void scenes_handle(void);
void scene_set_next(Scene *scene);



#endif
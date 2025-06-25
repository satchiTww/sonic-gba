#include "gba_objects.h"

OBJ_ATTR obj_buffer[OAM_MAX_ENTRIES];

void obj_update_oam()
{
    for (int i = 0; i < OAM_MAX_ENTRIES; i++)
        OAM_MEM[i] = obj_buffer[i]
    ;
}
#include "gba_objects.h"

SEC_EWRAM
OBJ_ATTR oam_buffer[OAM_MAX_ENTRIES];

u32 gObjCount = 0;

void obj_init_oam()
{
    for (int i = 0; i < OAM_MAX_ENTRIES; i++) {
        oam_buffer[i].affineMode = OBJ_DISABLE;
    }
    obj_update_oam(OAM_MAX_ENTRIES);
}
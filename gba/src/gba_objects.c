#include "gba_objects.h"

OBJ_ATTR oam_buffer[OAM_MAX_ENTRIES] SEC_EWRAM;

u8 obj_width_lookup[16] = {8, 16, 32, 64, 16, 32, 32, 64, 8, 8, 16, 32, 0, 0, 0, 0};
u8 obj_height_lookup[16] = {8, 16, 32, 64, 8, 8, 16, 32, 16, 32, 32, 64, 0, 0, 0, 0};

void obj_init_oam()
{
    for (int i = 0; i < OAM_MAX_ENTRIES; i++) {
        obj_set_attributes(&oam_buffer[i], ATTR0_HIDE, 0, 0);
    }
    dma3_cpy(OAM_MEM, oam_buffer, OAM_MAX_ENTRIES * 2, DMA_CPY32);
}
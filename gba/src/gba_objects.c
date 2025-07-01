#include "gba_objects.h"

SEC_EWRAM
OBJ_ATTR oam_buffer[OAM_MAX_ENTRIES];

void obj_init_oam()
{
    for (int i = 0; i < OAM_MAX_ENTRIES; i++) {
        obj_set_attributes(&oam_buffer[i], ATTR0_HIDE, 0, 0);
    }
    dma3_cpy(OAM_MEM, oam_buffer, OAM_MAX_ENTRIES * 2, DMA_CPY32);
}

void obj_update_oam()
{
    dma3_cpy(OAM_MEM, oam_buffer, OAM_MAX_ENTRIES * 2, DMA_CPY32);
    obj_clear_oam_buffer();
}
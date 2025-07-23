#include "gba_objects.h"

SEC_EWRAM
OBJ_ATTR oam_buffer[OAM_MAX_ENTRIES];
OBJ_AFFINE *oam_aff_buffer = (OBJ_AFFINE*)oam_buffer;

u8 obj_width_lookup[16] = {8, 16, 32, 64, 16, 32, 32, 64, 8, 8, 16, 32, 0, 0, 0, 0};
u8 obj_height_lookup[16] = {8, 16, 32, 64, 8, 8, 16, 32, 16, 32, 32, 64, 0, 0, 0, 0};

void obj_init_oam()
{
    for (int i = 0; i < OAM_MAX_ENTRIES; i++) {
        obj_set_attributes(&oam_buffer[i], ATTR0_HIDE, 0, 0);
    }
    for (int i = 0; i < OAM_MAX_ENTRIES/4; i++) {
        obj_set_aff_attr(&oam_aff_buffer[i], 1 << 8, 0, 0, 1 << 8);
    }

    dma3_cpy(OAM_MEM, oam_buffer, OAM_MAX_ENTRIES * 2, DMA_CPY32);
}
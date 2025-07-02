#include "gba.h"
#include "scenes.h"

static void irq_setup(void);
static void scenes_setup(void);

int main(void)
{
    irq_setup();

    scenes_setup();

    while (1)
    {
        key_poll();

        scenes_handle();

        VBlankIntrWait();
    }

    return 0;
}

static void irq_setup(void)
{
    irq_init();
    
    //set up vblank irq
    irq_reg_handler(IRQ_VBLANK, 0);
    REG_DISPSTAT  = DISPSTAT_VB_IRQ;
    REG_IE        = IRQ_VBLANK;
    REG_IME       = 1;
}

static void scenes_setup(void)
{
    //adds all scenes that will be used in the game
    scene_add(&testRoom);

    //loads the first scene that will be used when the game is initialized
    scene_set_next(&testRoom);
}
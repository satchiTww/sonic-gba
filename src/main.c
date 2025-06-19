#include "gba.h"
#include "data/backgrounds/TZ_bg0.h"

void irq_setup();

int main(void)
{
    irq_setup();

    while (1)
    {
        VBlankIntrWait();

        key_poll();
    }

    return 0;
}

void irq_setup()
{
    irq_init();
    
    //set up vblank irq
    irq_reg_handler(IRQ_VBLANK, 0);
    REG_DISPSTAT  = DISPSTAT_VB_IRQ;
    REG_IE        = IRQ_VBLANK;
    REG_IME       = 1;
}
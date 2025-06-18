#include "gba_registers.h"

static void (*irq_callbacks[14])(void) = { 0 };

void irq_register_handler(u16 irq_mask, void (*callback)(void))
{
    for (int i = 0; i < 14; i++) {
        if (irq_mask == (1 << i)) {
            irq_callbacks[i] = callback;
            return;
        }
    }
}

void irq_remove_handler(u16 irq_mask)
{
    for (int i = 0; i < 14; i++) {
        if (irq_mask == (1 << i)) {
            irq_callbacks[i] = 0;
            return;
        }
    }
}

__attribute__((target("arm")))
__attribute__((section(".iwram")))
void irq_master_handler(void)
{
    //Read pending flags
    u16 pending = REG_IF & REG_IE;

    //Loop until all pending bits are handled
    while (pending)
    {
        for (int i = 0; i < 14; i++) {
            u16 mask = (1u << i);
            if (pending & mask) {
                //call registered callback, if any
                if (irq_callbacks[i]) {
                    irq_callbacks[i]();
                }

                //Acknowledge (clear) this interrupt
                REG_IF = mask;
                REG_IFBIOS |= mask;

                //Remove from pending to avoid infinite loop
                pending &= ~mask;
            }
        }
        // Recompute in case another IRQ bit was set while servicing callbacks
        pending = REG_IF & REG_IE;
    }
}

void irq_initialize(void)
{
    REG_IME = 0;
    REG_IE = 0;
    REG_IF = 0xFFFF;

    REG_IRQ = irq_master_handler;
}
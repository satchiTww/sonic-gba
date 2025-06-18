#ifndef GBA_INTERRUPT
#define GBA_INTERRUPT

#include "gba_typedefs.h"

void irq_initialize(void);
void irq_register_handler(u16 irq_mask, void (*callback)(void));
void irq_remove_handler(u16 irq_mask);
void irq_master_handler(void);

/*=============IRQ REGs BITS================*/
#define IRQ_VBLANK 0x0001
#define IRQ_HBLANK 0x0002
//TODO: all the other interrupts

#endif
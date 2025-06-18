#ifndef GBA_REGISTERS_H
#define GBA_REGISTERS_H

#include "gba_typedefs.h"

/*=======================DISPLAY==============================*/
#define REG_DISPCNT  *((volatile u16*)0x04000000) //Display control
/*TODO ?: Stereoscopic mode enable*/
#define REG_DISPSTAT *((u16*)0x04000004)          //Display Status, display interrupt enable, (LYC)
#define REG_VCOUNT   *((volatile u16*)0x04000006) //Current display scanline position

#define REG_BG0CNT   *((u16*)0x04000008)          //Background 0 control
#define REG_BG1CNT   *((u16*)0x0400000A)          //Background 1 control
#define REG_BG2CNT   *((u16*)0x0400000C)          //Background 2 control
#define REG_BG3CNT   *((u16*)0x0400000E)          //Background 3 control

#define REG_BG0HOFS  *((u16*)0x04000010)          //Background 0 horizontal scroll
#define REG_BG0VOFS  *((u16*)0x04000012)          //Background 0 vertical scroll
#define REG_BG1HOFS  *((u16*)0x04000014)          //Background 1 horizontal scroll
#define REG_BG1VOFS  *((u16*)0x04000016)          //Background 1 vertical scroll
#define REG_BG2HOFS  *((u16*)0x04000018)          //Background 2 horizontal scroll
#define REG_BG2VOFS  *((u16*)0x0400001A)          //Background 2 vertical scroll
#define REG_BG3HOFS  *((u16*)0x0400001C)          //Background 3 horizontal scroll
#define REG_BG3VOFS  *((u16*)0x0400001E)          //Background 3 vertical scroll

/*====================INTERRUPTS=============================*/
#define REG_IRQ      *((func_ptr*)0x03007FFC)     //Interrupt Request
#define REG_IE       *((u16*)0x04000200)          //Interrupt Enable Register
#define REG_IF       *((volatile u16*)0x04000202) //Interrupt Flags Register
#define REG_IFBIOS   *((volatile u16*)0x03007FF8) //BIOS interrupt Flags
#define REG_WAITCNT  *((u16*)0x04000204)          //Wait State Control
#define REG_IME      *((u16*)0x04000208)          //Interrupt Master Enable
/*TODO 1:
-All the other display registers
-Sound registers
?Alternative DMG Sound register names
?DMA Transfer Channels
-Timer Registers
?Normal / SPI
?Multiplay
?UART
*/
/*=============KEYPAD=================*/
#define REG_KEYINPUT *((volatile u16*)0x04000130) //Keypad input
#define REG_KEYCNT   *((volatile u16*)0x04000132) //Keypad wake and interrupt control
/*TODO 2:
?Serial port (EXT.) control
-Interrupts
?Cartridge slot control
?System control
*/
#endif
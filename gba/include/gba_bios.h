#ifndef GBA_BIOS_H
#define GBA_BIOS_H

#include "gba_typedefs.h"

#if	defined	( __thumb__ )
#define	syscall(number)	 __asm ("SWI	  "#number"\n" :::  "r0", "r1", "r2", "r3")
#else
#define	syscall(number)	 __asm ("SWI	  "#number"	<< 16\n" :::"r0", "r1", "r2", "r3")
#endif

INLINE void SoftReset(void)
{    syscall(0x00);    }

INLINE void VBlankIntrWait(void)
{    syscall(0x05);    }

INLINE void Halt(void)
{    syscall(0x02);    }

#endif
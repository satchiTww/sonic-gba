#ifndef KEYS_H
#define KEYS_H

#include "gba_typedefs.h"
#include "gba_memmap.h"
#include "gba_registers.h"

//credits to Jasper “cearn” Vijn

extern u16 __key_curr, __key_prev;

#define KEY_A        0x0001
#define KEY_B        0x0002
#define KEY_SELECT   0x0004
#define KEY_START    0x0008
#define KEY_RIGHT    0x0010
#define KEY_LEFT     0x0020
#define KEY_UP       0x0040
#define KEY_DOWN     0x0080
#define KEY_R        0x0100
#define KEY_L        0x0200

#define KEY_MASK     0x03FF

#define KEY_DOWN_NOW(key) (~(REG_KEYINPUT) & key)

INLINE void key_poll()
{
    __key_prev= __key_curr;
    __key_curr= ~REG_KEYINPUT & KEY_MASK;
}

INLINE u32 key_curr_state()      {   return __key_curr;          }
INLINE u32 key_prev_state()      {   return __key_prev;          }
INLINE u32 key_is_down(u32 key)  {   return  __key_curr & key;   }
INLINE u32 key_is_up(u32 key)    {   return ~__key_curr & key;   }
INLINE u32 key_was_down(u32 key) {   return  __key_prev & key;   }
INLINE u32 key_was_up(u32 key)   {   return ~__key_prev & key;   }
// Transitional state checks.
INLINE u32 key_transit(u32 key)
{   return ( __key_curr ^  __key_prev) & key;  }
INLINE u32 key_held(u32 key)
{   return ( __key_curr &  __key_prev) & key;  }
INLINE u32 key_hit(u32 key)
{   return ( __key_curr &~ __key_prev) & key;  }
INLINE u32 key_released(u32 key)
{   return (~__key_curr &  __key_prev) & key;  }

#endif
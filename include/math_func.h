#ifndef MATH_FUNC_H
#define MATH_FUNC_H

#include "gba_typedefs.h"
#include <stdlib.h>

typedef s32 fixed8;

#define FIXED8(integer, fraction) (((integer) << (8)) | ((fraction) & (0xFF)))

typedef enum {
    UP,
    DOWN,
    LEFT,
    RIGHT
} Direction;

INLINE s32 mf_min(s32 a, s32 b)
{    return a < b ? a : b;    }

INLINE s32 mf_max(s32 a, s32 b)
{    return a > b ? a : b;    }

INLINE s32 mf_abs(s32 a)
{    return a < 0 ? -a : a;    }

INLINE s32 mf_sign(s32 a)
{    return a > 0 ? 1 : (a < 0 ? -1 : 0);    }

INLINE s32 fixed8_to_int(fixed8 x)
{    return (x >> 8);    }

extern const fixed8 sine_table[];

INLINE fixed8 angle_get_sin(u8 angle)
{    return sine_table[angle % 256];    }

INLINE fixed8 angle_get_cos(u8 angle)
{    return sine_table[(angle + 64) % 256];    }

INLINE void angle_calc_sine(u8 angle, fixed8 *sin, fixed8 *cos)
{
    if (sin != NULL) {
        *sin = sine_table[angle % 256];
    }
    if (cos != NULL) {
        *cos = sine_table[(angle + 64) % 256];
    }
}

u8 angle_get(int xDist, int yDist);

#endif
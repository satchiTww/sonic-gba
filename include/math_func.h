#ifndef MATH_FUNC_H
#define MATH_FUNC_H

#include "gba_typedefs.h"

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

extern fixed8 sine_table[];
extern u8 angle_table[];

INLINE fixed8 angle_sin(u8 angle)
{    return sine_table[angle % 256];    }

INLINE fixed8 angle_cos(u8 angle)
{    return sine_table[(angle + 64) % 256];    }

u8 angle_direction(int xDist, int yDist);

#endif
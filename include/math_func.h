#ifndef MATH_FUNC_H
#define MATH_FUNC_H

typedef s32 fixed8;

#define FIXED8(integer, fraction) (((integer) << (8)) | ((fraction) & (0xFF)))

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

#endif
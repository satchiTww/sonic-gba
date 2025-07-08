#ifndef GBA_TYPEDEFS_H
#define GBA_TYPEDEFS_H

#define INLINE static inline

#define ALIGN4    __attribute__((aligned(4)))
#define TARG_ARM  __attribute__((target("arm")))
#define SEC_IWRAM __attribute__((section(".iwram")))
#define SEC_EWRAM __attribute__((section(".ewram")))

#define ON 1
#define OFF 0

#define TRUE 1
#define FALSE 0

//unsigned types
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned long u32;

//signed types
typedef signed char s8;
typedef signed short s16;
typedef signed long s32;

typedef void (*func_ptr)(void);

#endif
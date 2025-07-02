#ifndef ASSETS_H
#define ASSETS_H

/* Import a binary file */
#define IMPORT_BIN(sect, file, sym) __asm ( \
    ".section " #sect "\n"                  \
    ".align 2\n"                            \
    ".global " #sym "\n"                    \
    #sym ":\n"                              \
    ".incbin \"" file "\"\n"                \
    ".global _sizeof_" #sym "\n"            \
    ".set _sizeof_" #sym ", . - " #sym "\n" \
    ".align 2\n"                            \
    ".section \".text\"\n")

#define IMPORT_BIN_TO_ROM(file, sym) IMPORT_BIN(".rodata", file, sym)

#define DEFINE_BIN16(sym) extern const unsigned short sym[], _sizeof_##sym[]

#define DEFINE_GBA_BG16(sym) \
    DEFINE_BIN16(sym##Tiles); \
    DEFINE_BIN16(sym##Map); \
    DEFINE_BIN16(sym##Pal) \

#endif
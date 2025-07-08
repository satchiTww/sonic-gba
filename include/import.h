#ifndef IMPORT_H
#define IMPORT_H

/* Import a binary file */
#define IMPORT_BIN(sect, file, sym) __asm ( \
    ".section " #sect "\n"                  \
    ".align 4\n"                            \
    ".global " #sym "\n"                    \
    #sym ":\n"                              \
    ".incbin \"" file "\"\n"                \
    ".global _sizeof_" #sym "\n"            \
    ".set _sizeof_" #sym ", . - " #sym "\n" \
    ".section \".text\"\n")

//Put binary data into rom section
#define IMPORT_BIN_TO_ROM(file, sym) IMPORT_BIN(".rodata", file, sym)

//Define u16 constants for the imported data
#define DEFINE_BIN16(sym) \
    extern const unsigned short sym[]; \
    extern unsigned int _sizeof_##sym[]

//Define u16 constants for tiles, map and pal data
#define DEFINE_GBA_BG16(sym) \
    DEFINE_BIN16(sym##Tiles); \
    DEFINE_BIN16(sym##Map); \
    DEFINE_BIN16(sym##Pal) \

#endif
#ifndef GBA_MEMMAP_H
#define GBA_MEMMAP_H

//General Internal Memory
#define BIOS     0x00000000
#define EWRAM    0x02000000 //external work ram. 256kb size. 16bit port.
#define IWRAM    0x03000000 //internal work ram. 32kb size.  32bit port.
#define IORAM    0X04000000 //i/o registers.

//Internal Display Memory
#define PALRAM   0x05000000 //Palette for BG and Sprites. 16bit port. BG: 0x05000000. Sprites: 0x05000200
#define VRAM     0x06000000 //store frame buffer in bitmap modes and tile/maps data. 96kb size. 16bit port.
#define OAM      0x07000000 //OBJ attribute memory. Control sprites. 32bit port.

#endif
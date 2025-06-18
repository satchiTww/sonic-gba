#include "gba.h"
#include "data/backgrounds/TZ_bg0.h"

int main(void)
{
    //Set up display
    REG_DISPCNT = DISPCNT_MODE_0 | DISPCNT_BG0 | DISPCNT_BG1 | DISPCNT_OBJ | DISPCNT_1DSPRT;

    REG_BG0CNT = BGCNT_PRIORITY3 |
                 BGCNT_CHARBLOCK0 |
                 BGCNT_SCRNBLOCK(28) |
                 BGCNT_SIZE0;

    REG_BG1CNT = BGCNT_PRIORITY2 |
                 BGCNT_CHARBLOCK0 |
                 BGCNT_SCRNBLOCK(29) |
                 BGCNT_SIZE0;

    //Load BG0
    load_palette(TZ_bg0Pal, TZ_bg0PalLen, 0);
    load_tileset(TZ_bg0Tiles, TZ_bg0TilesLen, 0, 0);
    load_tilemap(TZ_bg0Map, TZ_bg0MapLen, 28);

    while (1);

    return 0;
}
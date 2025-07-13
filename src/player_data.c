#include "player.h"
#include "data/include/sprite_data.h"
#include "data/include/animation_data.h"

playerCharData playerCharTable[NUM_OF_PLAYER_CHARS] = {
    [CHAR_TETO] = {teto_pal, (u32)_sizeof_teto_pal, animTeto, 5, 20}
};
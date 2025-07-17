#include "import.h"

//PALETTE
IMPORT_BIN_TO_ROM("data/bin/pal/tetoPal.bin", teto_pal);
IMPORT_BIN_TO_ROM("data/bin/pal/background_0.pal.bin", bg0Pal);
IMPORT_BIN_TO_ROM("data/bin/pal/test_zone_layout.pal.bin", test_zone_layoutPal);

//TILES
IMPORT_BIN_TO_ROM("data/bin/tiles/teto_idleTiles.bin", teto_idleTiles);
IMPORT_BIN_TO_ROM("data/bin/tiles/teto_walk_0Tiles.bin", teto_walk0Tiles);
IMPORT_BIN_TO_ROM("data/bin/tiles/teto_walk_1Tiles.bin", teto_walk1Tiles);
IMPORT_BIN_TO_ROM("data/bin/tiles/teto_walk_2Tiles.bin", teto_walk2Tiles);
IMPORT_BIN_TO_ROM("data/bin/tiles/teto_walk_3Tiles.bin", teto_walk3Tiles);
IMPORT_BIN_TO_ROM("data/bin/tiles/teto_walk_4Tiles.bin", teto_walk4Tiles);
IMPORT_BIN_TO_ROM("data/bin/tiles/teto_walk_5Tiles.bin", teto_walk5Tiles);
IMPORT_BIN_TO_ROM("data/bin/tiles/teto_walk_6Tiles.bin", teto_walk6Tiles);
IMPORT_BIN_TO_ROM("data/bin/tiles/teto_walk_7Tiles.bin", teto_walk7Tiles);
IMPORT_BIN_TO_ROM("data/bin/tiles/teto_run_0Tiles.bin", teto_run0Tiles);
IMPORT_BIN_TO_ROM("data/bin/tiles/teto_run_1Tiles.bin", teto_run1Tiles);
IMPORT_BIN_TO_ROM("data/bin/tiles/teto_run_2Tiles.bin", teto_run2Tiles);
IMPORT_BIN_TO_ROM("data/bin/tiles/teto_run_3Tiles.bin", teto_run3Tiles);
IMPORT_BIN_TO_ROM("data/bin/tiles/teto_push_0Tiles.bin", teto_push0Tiles);
IMPORT_BIN_TO_ROM("data/bin/tiles/teto_push_1Tiles.bin", teto_push1Tiles);
IMPORT_BIN_TO_ROM("data/bin/tiles/teto_push_2Tiles.bin", teto_push2Tiles);
IMPORT_BIN_TO_ROM("data/bin/tiles/teto_push_3Tiles.bin", teto_push3Tiles);

IMPORT_BIN_TO_ROM("data/bin/tiles/background_0.img.bin", bg0Tiles);
IMPORT_BIN_TO_ROM("data/bin/tiles/testzone_layout.img.bin", test_zone_layoutTiles);

//MAP
IMPORT_BIN_TO_ROM("data/bin/map/background_0.map.bin", bg0Map);
IMPORT_BIN_TO_ROM("data/bin/map/testzone_layout.map.bin", test_zone_layoutMap);

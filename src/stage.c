#include "stage.h"
#include "data/include/solid_tiles_data.h"

Stage stageTestRoom = {
    .mapWidth = 3072,
    .mapHeight = 320,
    .collisionMapData    = TestZoneMapIndex,
    .collisionHeightData = TestZoneHeightData,
    .collisionWidthData  = TestZoneWidthData,
    .collisionAngleData  = TestZoneAngleData,
};
#include "stage.h"
#include "data/include/solid_tiles_data.h"

StageData stageTestRoom = {
    .mapWidth = 2352,
    .mapHeight = 272,
    .collisionMapData = TestZoneMapIndex,
    .collisionHeightData = TestZoneHeightData,
    //.collisionWidthData
    .collisionAngleData = TestZoneAngleData,
};
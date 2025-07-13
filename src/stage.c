#include "stage.h"
#include "data/bin/collisionMap/TZ_CollisionMap.h"
#include "data/bin/solidTile/TZ_CollisionData.h"

StageData stageTestRoom = {
    .mapWidth = 1008,
    .mapHeight = 224,
    .collisionMapData = TZ_CollisionMap,
    .collisionHeightData = TZ_CollisionDataHeight,
    //.collisionWidthData
    .collisionAngleData = TZ_CollisionDataAngle,
};
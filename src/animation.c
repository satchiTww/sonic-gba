#include "animation.h"

void animation_tiles_play(const AnimatedTiles animTileset)
{
    static int frameTimer = 0;
    static int animationIndex = 0;

    frameTimer++;

    if (frameTimer >= animTileset.frameDuration[animationIndex]) {
        frameTimer = 0;

        animationIndex++;

        if (animationIndex >= animTileset.numOfFrames) {
            if (animTileset.isLoop)
                animationIndex = 0;
            else
                animationIndex = animTileset.numOfFrames;
        }
    }

    tiles_load(
        animTileset.frameTiles[animationIndex].data,
        animTileset.frameTiles[animationIndex].lenght,
        animTileset.frameTiles[animationIndex].char_block,
        animTileset.frameTiles[animationIndex].char_block_offset
    );
}
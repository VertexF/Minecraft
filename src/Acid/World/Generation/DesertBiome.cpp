#include "DesertBiome.h"

#include "TreeGenerator.h"

namespace acid 
{
    DesertBoime::DesertBoime(int seed) : Biome(getNoiseParameters(), 175, 150, seed)
    {
    }

    BlockID DesertBoime::getPlant(Random<std::minstd_rand>& rand) const
    {
        return BlockID::DEADSHRUB;
    }

    BlockID DesertBoime::getTopBlock(Random<std::minstd_rand>& rand) const
    {
        return BlockID::SAND;
    }

    void DesertBoime::makeTree(Random<std::minstd_rand>& rand, Chunk& chunk, int x, int y, int z) const
    {
        makeCactus(chunk, rand, x, y, z);
    }

    NoiseParameters DesertBoime::getNoiseParameters()
    {
        NoiseParameters heightParams;
        heightParams.octaves = 9;
        heightParams.amplitude = 80;
        heightParams.smoothness = 335;
        heightParams.heightOffset = -10;
        heightParams.roughness = 0.53;

        return heightParams;
    }
}
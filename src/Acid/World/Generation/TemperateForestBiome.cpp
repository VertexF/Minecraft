#include "TemperateForestBiome.h"

#include "TreeGenerator.h"

namespace acid 
{
    TemperateForestBiome::TemperateForestBiome(int seed) : Biome(getNoiseParameters(), 100, seed)
    {
    }

    BlockID TemperateForestBiome::getTopBlock(Random<std::minstd_rand>& rand) const
    {
        return rand.intInRange(0, 10) < 8 ? BlockID::GRASS : BlockID::DIRT;
    }

    void TemperateForestBiome::makeTree(Random<std::minstd_rand>& rand, Chunk& chunk, int x, int y, int z) const
    {
        makeOakTree(chunk, rand, x, y, z);
    }

    NoiseParameters TemperateForestBiome::getNoiseParameters()
    {
        NoiseParameters heightParams;
        heightParams.octaves = 9;
        heightParams.amplitude = 100;
        heightParams.smoothness = 195;
        heightParams.heightOffset = -15;
        heightParams.roughness = 0.50;

        return heightParams;
    }
}
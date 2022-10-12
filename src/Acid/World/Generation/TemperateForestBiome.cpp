#include "TemperateForestBiome.h"

#include "TreeGenerator.h"

namespace acid 
{
    TemperateForestBiome::TemperateForestBiome(int seed) : Biome(getNoiseParameters(), 55, 75, seed)
    {
    }

    BlockID TemperateForestBiome::getPlant(Random<std::minstd_rand>& rand) const
    {
        return BlockID::TALLGRASS;
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
        heightParams.octaves = 5;
        heightParams.amplitude = 100;
        heightParams.smoothness = 195;
        heightParams.heightOffset = -30;
        heightParams.roughness = 0.52;

        return heightParams;
    }
}
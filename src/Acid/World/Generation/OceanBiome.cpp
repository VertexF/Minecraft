#include "OceanBiome.h"

#include "TreeGenerator.h"

namespace acid 
{
    OceanBiome::OceanBiome(int seed) : Biome(getNoiseParameters(), 50, seed)
    {
    }

    BlockID OceanBiome::getTopBlock(Random<std::minstd_rand>& rand) const
    {
        return BlockID::GRASS;
    }

    void OceanBiome::makeTree(Random<std::minstd_rand>& rand, Chunk& chunk, int x, int y, int z) const
    {
        rand.intInRange(0, 5) < 3 ? makePalmTree(chunk, rand, x, y, z) : makeOakTree(chunk, rand, x, y, z);
    }

    NoiseParameters OceanBiome::getNoiseParameters()
    {
        NoiseParameters heightParams;
        heightParams.octaves = 9;
        heightParams.amplitude = 40;
        heightParams.smoothness = 100;
        heightParams.heightOffset = 0;
        heightParams.roughness = 0.52;

        return heightParams;
    }
}
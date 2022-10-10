#include "GrasslandBiome.h"

#include "TreeGenerator.h"

namespace acid 
{
    GrasslandBiome::GrasslandBiome(int seed) : Biome(getNoiseParameters(), 100, seed)
    {
    }

    BlockID GrasslandBiome::getTopBlock(Random<std::minstd_rand>& rand) const
    {
        return BlockID::GRASS;
    }

    void GrasslandBiome::makeTree(Random<std::minstd_rand>& rand, Chunk& chunk, int x, int y, int z) const
    {
        makeOakTree(chunk, rand, x, y, z);
    }

    NoiseParameters GrasslandBiome::getNoiseParameters()
    {
        NoiseParameters heightParams;
        heightParams.octaves = 9;
        heightParams.amplitude = 90;
        heightParams.smoothness = 335;
        heightParams.heightOffset = -5;
        heightParams.roughness = 0.50;

        return heightParams;
    }
}
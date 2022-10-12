#include "GrasslandBiome.h"

#include "TreeGenerator.h"

namespace acid 
{
    GrasslandBiome::GrasslandBiome(int seed) : Biome(getNoiseParameters(), 100, 50, seed)
    {
    }

    BlockID GrasslandBiome::getPlant(Random<std::minstd_rand>& rand) const
    {
        return rand.intInRange(0,10) > 6 ? BlockID::ROSE : BlockID::TALLGRASS;
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
        heightParams.amplitude = 85;
        heightParams.smoothness = 235;
        heightParams.heightOffset = -20;
        heightParams.roughness = 0.51;

        return heightParams;
    }
}
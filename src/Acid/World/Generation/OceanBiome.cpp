#include "OceanBiome.h"

#include "TreeGenerator.h"

namespace acid 
{
    OceanBiome::OceanBiome(int seed) : Biome(getNoiseParameters(), 50, 100, seed)
    {
    }

    BlockID OceanBiome::getPlant(Random<std::minstd_rand>& rand) const
    {
        return rand.intInRange(0, 10) > 6 ? BlockID::ROSE : BlockID::TALLGRASS;
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
        heightParams.octaves = 7;
        heightParams.amplitude = 43;
        heightParams.smoothness = 55;
        heightParams.heightOffset = 0;
        heightParams.roughness = 0.50;

        return heightParams;
    }
}
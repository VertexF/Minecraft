#include "Biome.h"

#include "TreeGenerator.h"

namespace acid 
{
    GrasslandBiome::GrasslandBiome(int seed) : _heightGenerator(seed)
    {
        NoiseParameters heightParams;
        heightParams.octaves = 9;
        heightParams.amplitude = 90;
        heightParams.smoothness = 335;
        heightParams.heightOffset = -5;
        heightParams.roughness = 0.50;

        _heightGenerator.setParameters(heightParams);
    }

    BlockID GrasslandBiome::getTopBlock(Random<std::minstd_rand>& rand) const
    {
        return BlockID::GRASS;
    }

    void GrasslandBiome::makeTree(Random<std::minstd_rand>& rand, Chunk& chunk, int x, int y, int z) const
    {
        makeOakTree(chunk, rand, x, y, z);
    }

    int GrasslandBiome::getHeight(int x, int z, int chunkX, int chunkZ) const
    {
        return _heightGenerator.getHeight(x, z, chunkX, chunkZ);
    }

    int GrasslandBiome::getTreeFrequency() const
    {
        return 100;
    }

    LightForestBiome::LightForestBiome(int seed) : _heightGenerator(seed)
    {
        NoiseParameters heightParams;
        heightParams.octaves = 9;
        heightParams.amplitude = 100;
        heightParams.smoothness = 195;
        heightParams.heightOffset = -15;
        heightParams.roughness = 0.50;

        _heightGenerator.setParameters(heightParams);
    }

    BlockID LightForestBiome::getTopBlock(Random<std::minstd_rand>& rand) const
    {
        return rand.intInRange(0, 10) < 8 ? BlockID::GRASS : BlockID::DIRT;
    }

    void LightForestBiome::makeTree(Random<std::minstd_rand>& rand, Chunk& chunk, int x, int y, int z) const
    {
        makeOakTree(chunk, rand, x, y, z);
    }

    int LightForestBiome::getHeight(int x, int z, int chunkX, int chunkZ) const
    {
        return _heightGenerator.getHeight(x, z, chunkX, chunkZ);
    }

    int LightForestBiome::getTreeFrequency() const
    {
        return 50;
    }

    DesertBoime::DesertBoime(int seed) : _heightGenerator(seed)
    {
        NoiseParameters heightParams;
        heightParams.octaves = 9;
        heightParams.amplitude = 80;
        heightParams.smoothness = 335;
        heightParams.heightOffset = 0;
        heightParams.roughness = 0.53;

        _heightGenerator.setParameters(heightParams);
    }

    BlockID DesertBoime::getTopBlock(Random<std::minstd_rand>& rand) const
    {
        return BlockID::SAND;
    }

    void DesertBoime::makeTree(Random<std::minstd_rand>& rand, Chunk& chunk, int x, int y, int z) const
    {
        makeCactus(chunk, rand, x, y, z);
    }

    int DesertBoime::getHeight(int x, int z, int chunkX, int chunkZ) const
    {
        return _heightGenerator.getHeight(x, z, chunkX, chunkZ);
    }

    int DesertBoime::getTreeFrequency() const
    {
        return 200;
    }
}
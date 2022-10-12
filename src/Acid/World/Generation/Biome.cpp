#include "Biome.h"

namespace acid 
{
    Biome::Biome(const NoiseParameters& paramters, int treeFreq, int plantFreq, int seed) :
        _heightGenerator(seed), _treeFreq(treeFreq), _plantFreq(plantFreq)
    {
        _heightGenerator.setParameters(paramters);
    }

    int Biome::getHeight(int x, int z, int chunkX, int chunkZ) const
    {
        return _heightGenerator.getHeight(x, z, chunkX, chunkZ);
    }

    int Biome::getTreeFrequency() const noexcept
    {
        return _treeFreq;
    }

    int Biome::getPlantFrequency() const noexcept
    {
        return _plantFreq;
    }
}
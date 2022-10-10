#include "Biome.h"

namespace acid 
{
    Biome::Biome(const NoiseParameters& paramters, int treeFreq, int seed) :
        _heightGenerator(seed), _treeFreq(treeFreq)
    {
        _heightGenerator.setParameters(paramters);
    }

    int Biome::getHeight(int x, int z, int chunkX, int chunkZ) const
    {
        return _heightGenerator.getHeight(x, z, chunkX, chunkZ);
    }

    int Biome::getTreeFrequency() const
    {
        return _treeFreq;
    }
}
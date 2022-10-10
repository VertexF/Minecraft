#ifndef BIOME_HDR
#define BIOME_HDR

#include "../../Maths/NoiseGenerator.h"
#include "../../Util/Random.h"
#include "../Block/BlockID.h"

namespace acid 
{
    class Chunk;

    struct Biome 
    {
    public:
        Biome(const NoiseParameters& paramters, int treeFreq, int seed);
        virtual ~Biome() = default;

        virtual BlockID getTopBlock(Random<std::minstd_rand>& rand) const = 0;
        virtual void makeTree(Random<std::minstd_rand>& rand, Chunk& chunk, int x, int y, int z) const = 0;

        int getHeight(int x, int z, int chunkX, int chunkZ) const;
        int getTreeFrequency() const;
    protected:
        virtual NoiseParameters getNoiseParameters() = 0;
    private:
        NoiseGenerator _heightGenerator;
        int _treeFreq;
    };
}

#endif // !BIOME_HDR

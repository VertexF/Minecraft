#include "TreeGenerator.h"

#include "../Chunk/Chunk.h"
#include "StructureBuilder.h"

namespace acid 
{
    void makeOakTree(Chunk& chunk, Random<std::minstd_rand>& rand, int x, int y, int z) 
    {
        //StructureBuilder builder
        for (int trunkY = 0; trunkY < rand.intInRange(4, 7); trunkY++)
        {
            chunk.setBlock(x, y + trunkY, z, BlockID::OAK_BARK);
        }
    }

    void makeCactus(Chunk& chunk, Random<std::minstd_rand>& rand, int x, int y, int z) 
    {
        //StructureBuilder builder
        for (int cactusY = 0; cactusY < rand.intInRange(4, 7); cactusY++)
        {
            chunk.setBlock(x, y + cactusY, z, BlockID::CACTUS);
        }
    }
}
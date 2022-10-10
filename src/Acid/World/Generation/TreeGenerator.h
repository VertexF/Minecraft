#ifndef TREE_GENERATOR_HDR
#define TREE_GENERATOR_HDR

#include "../../Util/Random.h"

namespace acid 
{
    class Chunk;

    void makeOakTree(Chunk& chunk, Random<std::minstd_rand>& rand, int x, int y, int z);
    void makePalmTree(Chunk& chunk, Random<std::minstd_rand>& rand, int x, int y, int z);
    void makeCactus(Chunk& chunk, Random<std::minstd_rand>& rand, int x, int y, int z);
}

#endif // !TREE_GENERATOR_HDR

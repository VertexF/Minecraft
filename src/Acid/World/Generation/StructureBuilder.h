#ifndef STRUCTURE_BUILDER_HDR
#define STRUCTURE_BUILDER_HDR

#include <vector>

#include "../Block/BlockID.h"

namespace acid
{
    class Chunk;

    class StructureBuilder
    {
        struct Block
        {
            Block(BlockID id, int x, int y, int z) :
                id(id), x(x), y(y), z(z)
            {
            }

            BlockID id;
            int x;
            int y;
            int z;
        };

    public:
        void build(Chunk& chunk);
        void makeColumn(int x, int z, int yStart, int height, BlockID block);

        void fill(int y, int xStart, int xEnd, int zStart, int zEnd, BlockID block);
        void addBlock(int x, int y, int z, BlockID block);

    private:
        std::vector<Block> _blocks;
    };
}

#endif // !STRUCTURE_BUILDER_HDR

#include "TreeGenerator.h"

#include "../Chunk/Chunk.h"
#include "StructureBuilder.h"

namespace acid 
{
    void makeOakTree(Chunk& chunk, Random<std::minstd_rand>& rand, int x, int y, int z) 
    {
        StructureBuilder builder;

        int hieght = rand.intInRange(4, 7);
        int leafSize = rand.intInRange(1, 3);

        int newY = hieght + y;
        builder.fill(newY, x - leafSize, x + leafSize, z - leafSize, z + leafSize, BlockID::OAK_LEAF);
        builder.fill(newY - 1, x - leafSize, x + leafSize, z - leafSize, z + leafSize, BlockID::OAK_LEAF);

        for(int32_t zLeaf = -leafSize; zLeaf < leafSize; zLeaf++)
        {
            builder.addBlock(x, newY + 1, z + zLeaf, BlockID::OAK_LEAF);
        }

        for (int32_t xLeaf = -leafSize; xLeaf < leafSize; xLeaf++)
        {
            builder.addBlock(x + xLeaf, newY + 1, z, BlockID::OAK_LEAF);
        }

        builder.makeColumn(x, z, y, hieght, BlockID::OAK_BARK);
        builder.build(chunk);
    }

    void makePalmTree(Chunk& chunk, Random<std::minstd_rand>& rand, int x, int y, int z) 
    {
        StructureBuilder builder;

        int hieght = rand.intInRange(4, 7);
        int diameter = rand.intInRange(4, 6);

        for (int32_t xLeaf = -diameter; xLeaf < diameter; xLeaf++)
        {
            builder.addBlock(x + xLeaf, y + hieght, z, BlockID::OAK_LEAF);
        }

        for (int32_t zLeaf = -diameter; zLeaf < diameter; zLeaf++)
        {
            builder.addBlock(x, y + hieght, z + zLeaf, BlockID::OAK_LEAF);
        }

        builder.addBlock(x, y + hieght - 1, z + diameter, BlockID::OAK_LEAF);
        builder.addBlock(x, y + hieght - 1, z - diameter, BlockID::OAK_LEAF);
        builder.addBlock(x + diameter, y + hieght - 1, z, BlockID::OAK_LEAF);
        builder.addBlock(x - diameter, y + hieght - 1, z, BlockID::OAK_LEAF);
        builder.addBlock(x, y + hieght - 1, z, BlockID::OAK_LEAF);

        builder.makeColumn(x, z, y, hieght, BlockID::OAK_BARK);
        builder.build(chunk);
    }

    void makeCactus(Chunk& chunk, Random<std::minstd_rand>& rand, int x, int y, int z) 
    {
        StructureBuilder builder;
        builder.makeColumn(x, z, y, rand.intInRange(4, 7), BlockID::CACTUS);
        builder.build(chunk);
    }
}
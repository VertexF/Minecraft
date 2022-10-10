#include "StructureBuilder.h"

#include "../Chunk/Chunk.h"

namespace acid
{
    void StructureBuilder::build(Chunk& chunk) 
    {
        for (auto& block : _blocks) 
        {
            chunk.setBlock(block.x, block.y, block.z, block.id);
        }
    }

    void StructureBuilder::makeColumn(int x, int z, int yStart, int height, BlockID block) 
    {
        for (int y = yStart; y < yStart + height; y++) 
        {
            _blocks.emplace_back(block, x, y, z);
        }
    }

    void StructureBuilder::fill(int y, int xStart, int xEnd, int zStart, int zEnd, BlockID block) 
    {
        for (int x = xStart; x < xEnd; ++x) 
        {
            for (int z = zStart; z < zEnd; ++z) 
            {
                _blocks.emplace_back(block, x, y, z);
            }
        }
    }

    void StructureBuilder::addBlock(int x, int y, int z, BlockID block) 
    {
        _blocks.emplace_back(block, x, y, z);
    }
}
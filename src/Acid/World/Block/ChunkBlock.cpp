#include "ChunkBlock.h"

namespace acid 
{
    ChunkBlock::ChunkBlock(uint8_t id) :
        id(id)
    {
    }

    ChunkBlock::ChunkBlock(BlockID id) :
        id(static_cast<uint8_t>(id))
    {
    }
}
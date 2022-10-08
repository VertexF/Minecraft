#include "ChunkBlock.h"

#include "../../Source/Global.h"

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

    const BlockDataHolder& ChunkBlock::getData() const
    {
        return BLOCK_DATABASE.getData(static_cast<BlockID>(id)).getBlockData();
    }

    const BlockType& ChunkBlock::getType() const 
    {
        return BLOCK_DATABASE.getBlock(static_cast<BlockID>(id));
    }

    BlockID ChunkBlock::getBlockID() const 
    {
        return static_cast<BlockID>(id);
    }
}
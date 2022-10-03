#ifndef CHUNK_BLOCK_HDR
#define CHUNK_BLOCK_HDR

#include "BlockID.h"

namespace acid 
{
    class BlockData;
    class BlockType;

    struct ChunkBlock 
    {
        ChunkBlock() = default;

        ChunkBlock(uint8_t id);
        ChunkBlock(BlockID id);

        const BlockData& getData() const;
        const BlockType& getType() const;
        BlockID getBlockID() const;

        bool operator==(ChunkBlock other) 
        {
            return (id == other.id);
        }

        bool operator!=(ChunkBlock other)
        {
            return (id != other.id);
        }

        uint8_t id = 0;
    };
}

#endif // !CHUNK_BLOCK_HDR

#ifndef CHUNK_BLOCK_HDR
#define CHUNK_BLOCK_HDR

#include "BlockID.h"

namespace acid 
{
    struct ChunkBlock 
    {
        ChunkBlock() = default;

        ChunkBlock(uint8_t id);
        ChunkBlock(BlockID id);

        uint8_t id = 0;
    };
}

#endif // !CHUNK_BLOCK_HDR

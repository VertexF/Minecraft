#ifndef CHUNK_BASE_HDR
#define CHUNK_BASE_HDR

#include "../Block/ChunkBlock.h"

namespace acid 
{
    class BaseChunk 
    {
    public:
        virtual ~BaseChunk() = default;
    protected:
        virtual ChunkBlock getBlock(int x, int y, int z) const = 0;
        virtual void setBlock(int x, int y, int z, const ChunkBlock& block) = 0;
    };
}

#endif // !CHUNK_BASE_HDR

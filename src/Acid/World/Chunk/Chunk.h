#ifndef CHUNK_HDR
#define CHUNK_HDR

#include <vector>
#include "ChunkSection.h"
#include "ChunkBase.h"
#include "../World.h"

namespace acid 
{
    class RenderMaster;

    class Chunk : public BaseChunk
    {
    public:
        Chunk(World& world);

        virtual ChunkBlock getBlock(int x, int y, int z) const override;
        virtual void setBlock(int x, int y, int z, const ChunkBlock& block) override;

        void drawChunks(RenderMaster& renderer);
    private:
        bool outOfBound(int x, int y, int z) const noexcept;

        std::vector<ChunkSection> _chunks;

        World* _world;
    };
}

#endif // !CHUNK_HDR

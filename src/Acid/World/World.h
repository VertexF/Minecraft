#ifndef WORLD_HDR
#define WORLD_HDR

#include <vector>
#include "Chunk/ChunkBase.h"
#include "Chunk/Chunk.h"

namespace acid 
{
    class RenderMaster;

    class World : public BaseChunk
    {
    public:
        World();
        virtual ~World() = default;

        virtual ChunkBlock getBlock(int x, int y, int z) const override;
        virtual void setBlock(int x, int y, int z, const ChunkBlock& block) override;

        void renderWorld(RenderMaster& master);
    private:
        Chunk _chunk;
    };
}

#endif // !WORLD_HDR

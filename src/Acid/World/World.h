#ifndef WORLD_HDR
#define WORLD_HDR

#include <vector>
#include <memory>
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

        void editBlock(int x, int y, int z, const ChunkBlock& block);

        void renderWorld(RenderMaster& master);
    private:
        std::vector<std::unique_ptr<Chunk>> _chunks;
    };
}

#endif // !WORLD_HDR

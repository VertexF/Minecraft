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
        void addChunk(int x, int z);

        void renderWorld(RenderMaster& master);
    private:
        std::vector<std::shared_ptr<Chunk>> _chunks;
        std::vector<std::shared_ptr<Chunk>> _changeChunks;
    };
}

#endif // !WORLD_HDR

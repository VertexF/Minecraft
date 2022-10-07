#ifndef WORLD_HDR
#define WORLD_HDR

#include <vector>
#include <set>
#include <memory>

#include "../Maths/Vector2XZ.h"
#include "Chunk/ChunkBase.h"
#include "Chunk/Chunk.h"
#include "Chunk/ChunkManager.h"

namespace acid 
{
    class RenderMaster;
    class Camera;

    class World : public BaseChunk
    {
    public:
        World();
        virtual ~World() = default;

        virtual ChunkBlock getBlock(int x, int y, int z) const override {}
        ChunkBlock getBlock(int x, int y, int z);

        virtual void setBlock(int x, int y, int z, const ChunkBlock& block) override;

        void update(const Camera& camera);

        void renderWorld(RenderMaster& master);
    private:
        ChunkManager _chunkManager;
        std::unordered_set<sf::Vector3i> _rebuildChunks;
    };
}

#endif // !WORLD_HDR

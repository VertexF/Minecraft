#ifndef CHUNK_HDR
#define CHUNK_HDR

#include <vector>
#include <memory>

#include "ChunkSection.h"
#include "ChunkBase.h"

namespace acid 
{
    class RenderMaster;
    class World;

    class Chunk : public BaseChunk
    {
    public:
        Chunk(World& world, const sf::Vector2i& location);

        void makeAllMesh();

        virtual ChunkBlock getBlock(int x, int y, int z) const override;
        virtual void setBlock(int x, int y, int z, const ChunkBlock& block) override;

        void drawChunks(RenderMaster& renderer);
    private:
        bool outOfBound(int x, int y, int z) const noexcept;

        std::vector<std::unique_ptr<ChunkSection>> _chunkSections;
        sf::Vector2i _location;
        World* _world;

        bool _isLoaded;
    };
}

#endif // !CHUNK_HDR

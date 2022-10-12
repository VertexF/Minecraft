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
    class Camera;

    class Chunk : public BaseChunk
    {
    public:
        Chunk(World& world, const sf::Vector2i& location);

        bool makeMesh();

        virtual ChunkBlock getBlock(int x, int y, int z) const noexcept override;
        virtual void setBlock(int x, int y, int z, const ChunkBlock& block) override;

        void drawChunks(RenderMaster& renderer, const Camera& camera);

        bool hasLoaded() const noexcept;
        void load();

        ChunkSection& getSection(int index);

        const sf::Vector2i& getLocation() const { return _location; }
    private:
        void addSection();
        void addSectionsBlockTarget(int blockY);
        void addSectionsIndexTarget(int index);

        bool outOfBound(int x, int y, int z) const noexcept;

        std::vector<std::unique_ptr<ChunkSection>> _chunkSections;
        sf::Vector2i _location;
        World* _world;

        bool _isLoaded;
    };
}

#endif // !CHUNK_HDR

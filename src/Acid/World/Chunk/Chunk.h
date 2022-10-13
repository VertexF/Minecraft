#ifndef CHUNK_HDR
#define CHUNK_HDR

#include <vector>
#include <memory>

#include "ChunkSection.h"
#include "ChunkBase.h"
#include "../../Util/Array2D.h"

namespace acid 
{
    class RenderMaster;
    class World;
    class Camera;
    class TerrianGenerator;

    class Chunk : public BaseChunk
    {
    public:
        Chunk(World& world, const sf::Vector2i& location);

        bool makeMesh(const Camera& camera);

        virtual ChunkBlock getBlock(int x, int y, int z) const noexcept override;
        virtual void setBlock(int x, int y, int z, const ChunkBlock& block) override;
        int getHeightAt(int x, int z);

        void drawChunks(RenderMaster& renderer, const Camera& camera);

        bool hasLoaded() const noexcept;
        void load(TerrianGenerator& generator);

        ChunkSection& getSection(int index);
        void deleteMeshes();

        const sf::Vector2i& getLocation() const;
    private:
        void addSection();
        void addSectionsBlockTarget(int blockY);
        void addSectionsIndexTarget(int index);

        bool outOfBound(int x, int y, int z) const noexcept;

        std::vector<std::unique_ptr<ChunkSection>> _chunkSections;
        Array2D<int, CHUNK_SIZE> _highestBlock;
        sf::Vector2i _location;
        World* _world;

        bool _isLoaded;
    };
}

#endif // !CHUNK_HDR

#ifndef CHUNK_SECTION_HDR
#define CHUNK_SECTION_HDR

#include <array>

#include <SFML/Graphics.hpp>

#include "../WorldConstants.h"
#include "../Block/ChunkBlock.h"
#include "ChunkMesh.h"
#include "ChunkBase.h"

namespace acid 
{
    class World;

    class ChunkSection : public BaseChunk
    {
    public:
        ChunkSection(const sf::Vector3i& position, World& world);

        void setBlock(int x, int y, int z, const ChunkBlock& block) override;
        ChunkBlock getBlock(int x, int y, int z) const override;

        void makeMesh();
        void bufferMesh();

        const sf::Vector3i getLocation() const noexcept;
        bool hasMesh() const noexcept;
        bool hasBuffered() const noexcept;
        void setHasMesh(bool meshBool);

        ChunkMesh &getMesh();
    private:
        sf::Vector3i toWorldPosition(int x, int y, int z) const;

        static bool outOfBounds(int value);
        static int getIndex(int x, int y, int z);

        sf::Vector3i _location;
        std::array<ChunkBlock, CHUNK_VOLUME> _blocks;
        ChunkMesh _mesh;

        World* _world;

        bool _hasMesh;
        bool _hasBufferedMesh;
    };
}

#endif // !CHUNK_SECTION_HDR

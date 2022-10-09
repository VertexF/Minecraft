#ifndef CHUNK_SECTION_HDR
#define CHUNK_SECTION_HDR

#include <array>

#include <SFML/Graphics.hpp>

#include "../WorldConstants.h"
#include "../Block/ChunkBlock.h"
#include "ChunkMesh.h"
#include "ChunkBase.h"
#include "../../Physics/AABB.h"
#include "../Block/BlockData.h"

namespace acid 
{
    class World;

    class ChunkSection : public BaseChunk
    {
        class Layer
        {
        public:
            void update(ChunkBlock chunk)
            {
                if (chunk.getData().isOpaque)
                {
                    _solidBlockCount--;
                }
                else
                {
                    _solidBlockCount++;
                }
            }

            bool isAllSolid() const
            {
                return _solidBlockCount == CHUNK_AREA;
            }

        private:
            int _solidBlockCount = 0;
        };

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

        const Layer& getLayer(int layer) const;
        ChunkSection& getAdjacent(int dx, int dz);

        ChunkMesh &getMesh();
        AABB getCurrentAABB() const;
    private:
        sf::Vector3i toWorldPosition(int x, int y, int z) const;

        static bool outOfBounds(int value);
        static int getIndex(int x, int y, int z);

        sf::Vector3i _location;
        std::array<Layer, CHUNK_SIZE> _layers;
        std::array<ChunkBlock, CHUNK_VOLUME> _blocks;
        ChunkMesh _mesh;
        AABB _aabb;

        World* _world;

        bool _hasMesh;
        bool _hasBufferedMesh;
    };
}

#endif // !CHUNK_SECTION_HDR

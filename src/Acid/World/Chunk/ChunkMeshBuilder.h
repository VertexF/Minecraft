#ifndef CHUNK_MESH_BUILDER_HDR
#define CHUNK_MESH_BUILDER_HDR

#include <vector>
#include <SFML/Graphics.hpp>
#include <GL/glew.h>

namespace acid 
{
    class ChunkSection;
    class ChunkMesh;
    class BlockData;
    class BlockDataHolder;

    class ChunkMeshBuilder 
    {
    public:
        ChunkMeshBuilder(ChunkSection& chunk);

        void buildMesh(ChunkMesh& chunk);
    private:
        void tryAddFaceToMesh(const std::vector<GLfloat>& blockFace,
                              const sf::Vector2i& textureCoords,
                              const sf::Vector3i& blockPosition,
                              const sf::Vector3i& blockFacing);

        bool shouldMakeFace(const sf::Vector3i& adjBlock, const BlockDataHolder& blockData);

        ChunkSection* _chunk = nullptr;
        ChunkMesh* _mesh = nullptr;

        const BlockDataHolder* _blockData = nullptr;
    };
}

#endif // !CHUNK_MESH_BUILDER_HDR

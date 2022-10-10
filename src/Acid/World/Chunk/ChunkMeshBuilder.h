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
    class ChunkSection;

    class ChunkMeshBuilder 
    {
    public:
        ChunkMeshBuilder(ChunkSection& chunkSection, ChunkMesh& chunkMesh);

        void buildMesh();
    private:
        void tryAddFaceToMesh(const std::vector<GLfloat>& blockFace,
                              const sf::Vector2i& textureCoords,
                              const sf::Vector3i& blockPosition,
                              const sf::Vector3i& blockFacing,
                              GLfloat cardinalLight);

        bool shouldMakeFace(const sf::Vector3i& adjBlock, const BlockDataHolder& blockData);
        bool shouldMakeLayer(int layer);

        ChunkSection* _sectionChunk = nullptr;
        ChunkMesh* _chunkMesh = nullptr;
        ChunkSection* _chunkSection = nullptr;

        const BlockDataHolder* _blockData = nullptr;
    };
}

#endif // !CHUNK_MESH_BUILDER_HDR

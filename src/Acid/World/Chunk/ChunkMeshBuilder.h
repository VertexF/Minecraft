#ifndef CHUNK_MESH_BUILDER_HDR
#define CHUNK_MESH_BUILDER_HDR

#include <vector>
#include <SFML/Graphics.hpp>
#include <GL/glew.h>

#include "../Block/ChunkBlock.h"
#include "../Chunk/ChunkMesh.h"

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
        ChunkMeshBuilder(ChunkSection& chunkSection, ChunkMeshCollection& chunkMeshes);

        void buildMesh();
    private:
        void setActiveMesh(ChunkBlock block);

        void addXBlockToMesh(const sf::Vector2i& textureCoords, 
                             const sf::Vector3i& blockPosition);

        void tryAddFaceToMesh(const std::vector<GLfloat>& blockFace,
                              const sf::Vector2i& textureCoords,
                              const sf::Vector3i& blockPosition,
                              const sf::Vector3i& blockFacing,
                              GLfloat cardinalLight);

        bool shouldMakeFace(const sf::Vector3i& adjBlock, const BlockDataHolder& blockData);
        bool shouldMakeLayer(int layer);
        
        ChunkMeshCollection* _chunkMeshes = nullptr;
        ChunkMesh* _activeMesh = nullptr;
        ChunkSection* _chunkSection = nullptr;

        const BlockDataHolder* _blockData = nullptr;
    };
}

#endif // !CHUNK_MESH_BUILDER_HDR

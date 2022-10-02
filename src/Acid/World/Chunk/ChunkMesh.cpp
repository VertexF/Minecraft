#include "ChunkMesh.h"

#include "../WorldConstants.h"

namespace acid 
{
    ChunkMesh::ChunkMesh() 
    {
    }

    void ChunkMesh::addFace(const std::vector<GLfloat>& blockFace, const std::vector<GLfloat>& textureCoords,
                            const sf::Vector3i& chunkPosition, const sf::Vector3i& blockPosition) 
    {
        auto& vertices = _mesh.vertexPosition;
        auto& texCoords = _mesh.textureCoords;
        auto& indices = _mesh.indices;

        texCoords.insert(texCoords.end(), textureCoords.begin(), textureCoords.end());

        for (int vertexName = 0, index = 0; vertexName < 4; vertexName++) 
        {
            vertices.push_back(blockFace[index++] + chunkPosition.x * CHUNK_SIZE + blockPosition.x);
            vertices.push_back(blockFace[index++] + chunkPosition.y * CHUNK_SIZE + blockPosition.y);
            vertices.push_back(blockFace[index++] + chunkPosition.z * CHUNK_SIZE + blockPosition.z);
        }

        indices.insert(indices.end(),
            {
                _indexIndex,
                _indexIndex + 1,
                _indexIndex + 2,

                _indexIndex + 2,
                _indexIndex + 3,
                _indexIndex
            });

        _indexIndex += 4;
    }

    void ChunkMesh::bufferMesh() 
    {
        _model.addData(_mesh);

        _mesh.vertexPosition.clear();
        _mesh.textureCoords.clear();
        _mesh.indices.clear();

        _mesh.vertexPosition.shrink_to_fit();
        _mesh.textureCoords.shrink_to_fit();
        _mesh.indices.shrink_to_fit();

        _indexIndex = 0;
    }

    const Model& ChunkMesh::getModel() const 
    {
        return _model;
    }
}
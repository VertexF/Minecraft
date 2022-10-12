#ifndef CHUNK_MESH_HDR
#define CHUNK_MESH_HDR

#include <vector>
#include <SFML/Graphics.hpp>

#include "../../Source/Mesh.h"
#include "../../Source/Model.h"

namespace acid 
{
    class ChunkMesh 
    {
    public:
        ChunkMesh();
        void addFace(const std::vector<GLfloat>& blockFace, 
                     const std::vector<GLfloat>& textureCoords, 
                     const sf::Vector3i& chunkPosition, 
                     const sf::Vector3i& blockPosition,
                     GLfloat cardinalLight, bool isXMesh);

        void bufferMesh();
        const Model& getModel() const;
        int getTotalFaces() const;

        bool isXMesh() const;
    private:
        Mesh _mesh;
        Model _model;
        GLuint _indexIndex = 0;

        std::vector<GLfloat> _light;

        int _faces;
        bool _isXMesh;
    };

    struct ChunkMeshCollection
    {
        ChunkMesh solidMesh;
        ChunkMesh waterMesh;
    };
}

#endif // !CHUNK_MESH_HDR

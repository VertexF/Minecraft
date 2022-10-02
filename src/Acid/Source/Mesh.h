#ifndef MESH_HDR
#define MESH_HDR

#include <vector>

#include <GL/glew.h>

namespace acid 
{
    struct Mesh
    {
        std::vector<GLfloat> vertexPosition;
        std::vector<GLfloat> textureCoords;
        std::vector<GLuint> indices;
    };
}

#endif // !MESH_HDR

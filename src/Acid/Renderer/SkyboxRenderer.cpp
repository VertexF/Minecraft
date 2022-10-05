#include "SkyboxRenderer.h"

#include <vector>

#include <GL/glew.h>

namespace acid 
{
    SkyRenderer::SkyRenderer() 
    {
        constexpr GLfloat SIZE = 500;
        std::vector<GLfloat> texCoords = 
        {
            //back
            SIZE, -SIZE, -SIZE,
            -SIZE, -SIZE, -SIZE,
            -SIZE, SIZE, -SIZE,
            SIZE, SIZE, -SIZE,

            //front
            -SIZE, -SIZE, SIZE,
            SIZE, -SIZE, SIZE,
            SIZE, SIZE, SIZE,
            -SIZE, SIZE, SIZE,

            //right
            SIZE, -SIZE, SIZE,
            SIZE, -SIZE, -SIZE,
            SIZE, SIZE, -SIZE,
            SIZE, SIZE, SIZE,

            //left
            -SIZE, -SIZE, -SIZE,
            -SIZE, -SIZE, SIZE,
            -SIZE, SIZE, SIZE,
            -SIZE, SIZE, -SIZE,

            //top
            -SIZE, SIZE, SIZE,
            SIZE, SIZE, SIZE,
            SIZE, SIZE, -SIZE,
            -SIZE, SIZE, -SIZE,

            //bottom
            -SIZE, -SIZE, -SIZE,
            SIZE, -SIZE, -SIZE,
            SIZE, -SIZE, SIZE,
            -SIZE, -SIZE, SIZE
        };


    }
}
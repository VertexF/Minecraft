#include "SkyboxRenderer.h"

#include <vector>

#include <GL/glew.h>

#include "../Source/Camera.h"
#include "../Source/GL/GLFunctions.h"

namespace acid 
{
    SkyRenderer::SkyRenderer() 
    {
        constexpr GLfloat SIZE = 500;
        std::vector<GLfloat> vertexCoords = 
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

        std::vector<GLuint> indices
        {
            0, 1, 2,
            2, 3, 0,

            4, 5, 6,
            6, 7, 4,

            8, 9, 10,
            10, 11, 8,

            12, 13, 14,
            14, 15, 12,

            16, 17, 18,
            18, 19, 16,

            20, 21, 22,
            22, 23, 20
        };

        _skyCude.genVAO();
        _skyCude.addVBO(3, vertexCoords);
        _skyCude.addEBO(indices);

        _cubeTexture.loadFromFile(
            {
                "right",
                "left",
                "top",
                "bottom",
                "back",
                "front"
            });
    }

    void SkyRenderer::render(const Camera& camera)
    {
        _shader.useProgram();
        _skyCude.bindVAO();
        _cubeTexture.bindTexture();

        _shader.loadViewMatrix(camera.getViewMatrix());
        _shader.loadProjectionMatrix(camera.getProjectionViewMatrix());

        drawElements(_skyCude.getIndicesCount());
    }
}
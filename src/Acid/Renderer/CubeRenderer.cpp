#include "CubeRenderer.h"

#include "QuadRenderer.h"

#include "../Source/Camera.h"
#include "../Maths/Matrix.h"
#include "../Source/Entity.h"

namespace acid
{
    CubeRenderer::CubeRenderer()
    {
        _basicTexture.loadFromFile("Test");

        std::vector<GLfloat> vertexCoords
        {
            //Back
            1.f, 0.f, 0.f,
            0.f, 0.f, 0.f,
            0.f, 1.f, 0.f,
            1.f, 1.f, 0.f,

            //Front
            0.f, 0.f, 1.f,
            1.f, 0.f, 1.f,
            1.f, 1.f, 1.f,
            0.f, 1.f, 1.f,

            //Right
            1.f, 0.f, 1.f,
            1.f, 0.f, 0.f,
            1.f, 1.f, 0.f,
            1.f, 1.f, 1.f,

            //left
            0.f, 0.f, 0.f,
            0.f, 0.f, 1.f,
            0.f, 1.f, 1.f,
            0.f, 1.f, 0.f,

            //Top
            0.f, 1.f, 1.f,
            1.f, 1.f, 1.f,
            1.f, 1.f, 0.f,
            0.f, 1.f, 0.f,

            //Bottom
            0.f, 0.f, 0.f,
            1.f, 0.f, 0.f,
            1.f, 0.f, 1.f,
            0.f, 0.f, 1.f
        };

        std::vector<GLfloat> texCoords
        {
            0.f, 1.f,
            1.f, 1.f,
            1.f, 0.f,
            0.f, 0.f,

            0.f, 1.f,
            1.f, 1.f,
            1.f, 0.f,
            0.f, 0.f,

            0.f, 1.f,
            1.f, 1.f,
            1.f, 0.f,
            0.f, 0.f,

            0.f, 1.f,
            1.f, 1.f,
            1.f, 0.f,
            0.f, 0.f,

            0.f, 1.f,
            1.f, 1.f,
            1.f, 0.f,
            0.f, 0.f,

            0.f, 1.f,
            1.f, 1.f,
            1.f, 0.f,
            0.f, 0.f
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

        _cubeModel.addData(vertexCoords, texCoords, indices);
    }

    void CubeRenderer::add(const glm::vec3& position)
    {
        _cubes.push_back(position);
    }

    void CubeRenderer::render(const Camera& camera)
    {
        glEnable(GL_CULL_FACE);

        _shader.useProgram();
        _cubeModel.bindVAO();
        _basicTexture.bindTexture();

        _shader.loadProjectionViewMatrix(camera.getProjectionViewMatrix());

        for (auto& cube : _cubes)
        {
            _shader.loadModelMatrix(makeModelMatrix({ cube, { 0, 0, 0 } }));
            glDrawElements(GL_TRIANGLES, _cubeModel.getIndicesCount(), GL_UNSIGNED_INT, nullptr);
        }

        _cubes.clear();
    }
}

#include "CubeRenderer.h"

#include "QuadRenderer.h"

#include "../Source/Camera.h"
#include "../Maths/Matrix.h"
#include "../Source/Entity.h"
#include "../Source/GL/GLFunctions.h"
#include "../Source/Entity.h"

namespace acid
{
    CubeRenderer::CubeRenderer() : _textureAtlas("DefaultPack2")
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

        auto top = _textureAtlas.getTexture({ 0, 0 });
        auto side = _textureAtlas.getTexture({ 1, 0 });
        auto bottom = _textureAtlas.getTexture({ 2, 0 });

        std::vector<GLfloat> texCoords;
        texCoords.insert(texCoords.end(), side.begin(), side.end());
        texCoords.insert(texCoords.end(), side.begin(), side.end());
        texCoords.insert(texCoords.end(), side.begin(), side.end());
        texCoords.insert(texCoords.end(), side.begin(), side.end());
        texCoords.insert(texCoords.end(), top.begin(), top.end());
        texCoords.insert(texCoords.end(), bottom.begin(), bottom.end());

        _cubeModel.addData({ vertexCoords, texCoords, indices });
    }

    void CubeRenderer::add(const Entity& entity)
    {
        _cubes.push_back(&entity);
    }

    void CubeRenderer::render(const Camera& camera)
    {
        if (_cubes.empty()) 
        {
            return;
        }

        _shader.useProgram();
        _cubeModel.bindVAO();
        _textureAtlas.bindTexture();

        _shader.loadProjectionViewMatrix(camera.getProjectionViewMatrix());

        for (auto& cube : _cubes)
        {
            _shader.loadModelMatrix(makeModelMatrix(*cube));
            drawElements(_cubeModel.getIndicesCount());
        }

        _cubes.clear();
    }
}

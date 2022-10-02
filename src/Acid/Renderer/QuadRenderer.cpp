#include "QuadRenderer.h"

#include "../Source/Camera.h"
#include "../Maths/Matrix.h"
#include "../Source/Entity.h"

namespace acid 
{
    QuadRenderer::QuadRenderer() 
    {
        _basicTexture.loadFromFile("Test");

        _quadModel.addData({
            {
                -0.5,  0.5, 0.0,
                 0.5,  0.5, 0.0,
                 0.5, -0.5, 0.0,
                -0.5, -0.5, 0.0,
            },
            {
                0, 1,
                1, 1,
                1, 0,
                0, 0
            },
            {
                0, 1, 2,
                2, 3, 0
            } });
    }

    void QuadRenderer::add(const glm::vec3& position) 
    {
        _quads.push_back(position);
    }

    void QuadRenderer::renderQuads(const Camera& camera) 
    {
        _shader.useProgram();
        _quadModel.bindVAO();
        _basicTexture.bindTexture();

        _shader.loadProjectionViewMatrix(camera.getProjectionViewMatrix());

        for (auto& quad : _quads) 
        {
            _shader.loadModelMatrix(makeModelMatrix({ quad, { 0, 0, 0 } }));
            glDrawElements(GL_TRIANGLES, _quadModel.getIndicesCount(), GL_UNSIGNED_INT, nullptr);
        }

        _quads.clear();
    }
}
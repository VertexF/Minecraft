#include "WaterRenderer.h"

#include "../Source/Global.h"
#include "../Source/Camera.h"
#include "../World/Chunk/ChunkMesh.h"
#include "../Source/GL/GLFunctions.h"

namespace acid 
{
    void WaterRenderer::add(const ChunkMesh& mesh)
    {
        _chunks.push_back(&mesh);
    }

    void WaterRenderer::render(const Camera& camera)
    {
        if (_chunks.empty())
        {
            return;
        }

        glEnable(GL_BLEND);
        glDisable(GL_CULL_FACE);

        _shader.useProgram();
        _shader.loadProjectionViewMatrix(camera.getProjectionViewMatrix());
        //_shader.addTime(_timer.getElapsedTime().asSeconds());

        for (const ChunkMesh* mesh : _chunks)
        {
            const ChunkMesh& currentMesh = *mesh;

            currentMesh.getModel().bindVAO();
            drawElements(currentMesh.getModel().getIndicesCount());
        }

        _chunks.clear();
    }
}
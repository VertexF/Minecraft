#include "ChunkRenderer.h"

#include "../Source/Global.h"
#include "../Source/Camera.h"
#include "../World/Chunk/ChunkMesh.h"
#include "../Source/GL/GLFunctions.h"

namespace acid 
{
    void ChunkRenderer::add(const ChunkMesh& mesh) 
    {
        _chunks.push_back(&mesh);
    }

    void ChunkRenderer::render(const Camera& camera)
    {
        _shader.useProgram();
        BLOCK_DATABASE.textureAtlas.bindTexture();

        _shader.loadProjectionViewMatrix(camera.getProjectionViewMatrix());

        for (const ChunkMesh* mesh : _chunks)
        {
            const ChunkMesh& currentMesh = *mesh;

            currentMesh.getModel().bindVAO();
            drawElements(currentMesh.getModel().getIndicesCount());
        }

        _chunks.clear();
    }
}
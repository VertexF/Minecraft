#include "ChunkRenderer.h"

#include "../Source/Global.h"
#include "../Source/Camera.h"
#include "../World/Chunk/ChunkMesh.h"

namespace acid 
{
    void ChunkRenderer::add(const ChunkMesh& mesh) 
    {
        _chunks.push_back(&mesh);
    }

    void ChunkRenderer::render(const Camera& camera)
    {
        glEnable(GL_CULL_FACE);

        _shader.useProgram();
        BLOCK_DATABASE.textureAtlas.bindTexture();

        _shader.loadProjectionViewMatrix(camera.getProjectionViewMatrix());

        for (const ChunkMesh* mesh : _chunks)
        {
            const ChunkMesh& currentMesh = *mesh;

            currentMesh.getModel().bindVAO();
            glDrawElements(GL_TRIANGLES, currentMesh.getModel().getIndicesCount(), GL_UNSIGNED_INT, nullptr);
        }

        _chunks.clear();
    }
}
#include "RenderMaster.h"

#include <GL/glew.h>
#include <SFML/Graphics.hpp>

#include "../World/Chunk/ChunkMesh.h"

namespace acid
{
    void RenderMaster::drawQuad(const glm::vec3& pos)
    {
        _quadRenderer.add(pos);
    }

    void RenderMaster::drawCube(const glm::vec3& pos)
    {
        _cubeRenderer.add(pos);
    }

    void RenderMaster::drawChunk(const ChunkMesh& mesh)
    {
        _chunkRenderer.add(mesh);
    }

    void RenderMaster::finishRender(sf::RenderWindow& window, const Camera& camera) 
    {
        glClearColor(0.1, 0.5, 1.0, 1.0);
        glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
        glEnable(GL_DEPTH_TEST);

        //_quadRenderer.renderQuads(camera);
        //_cubeRenderer.render(camera);
        _chunkRenderer.render(camera);

        window.display();
    }
}
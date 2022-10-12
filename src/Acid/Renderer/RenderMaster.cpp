#include "RenderMaster.h"

#include <GL/glew.h>
#include <SFML/Graphics.hpp>

#include "../World/Chunk/ChunkSection.h"
#include "../World/Chunk/ChunkMesh.h"
#include "../Source/Entity.h"

namespace acid
{
    void RenderMaster::drawQuad(const glm::vec3& pos)
    {
        _quadRenderer.add(pos);
    }

    void RenderMaster::drawCube(const Entity& entity)
    {
        _cubeRenderer.add(entity);
    }

    void RenderMaster::drawChunk(const ChunkSection& chunk)
    {
        const ChunkMesh& solidMesh = chunk.getMeshes().solidMesh;
        const ChunkMesh& waterMesh = chunk.getMeshes().waterMesh;

        if (solidMesh.getTotalFaces() > 0) 
        {
            _chunkRenderer.add(solidMesh);
        }
        if (waterMesh.getTotalFaces() > 0)
        {
            _chunkRenderer.add(waterMesh);
        }
    }

    void RenderMaster::drawSFML(const sf::Drawable& drawable)
    {
        _sfmlRenderer.add(drawable);
    }

    void RenderMaster::drawSky() 
    {
        _drawSky = true;
    }

    void RenderMaster::finishRender(sf::RenderWindow& window, const Camera& camera) 
    {
        glClearColor(0.1, 0.5, 1.0, 1.0);
        glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
        glEnable(GL_DEPTH_TEST);
        glEnable(GL_CULL_FACE);

        //_quadRenderer.render(camera);
        //_cubeRenderer.render(camera);
        _chunkRenderer.render(camera);
        _waterRender.render(camera);

        if (_drawSky) 
        {
            glDisable(GL_CULL_FACE);
            _skyRenderer.render(camera);
            _drawSky = false;
        }

        _sfmlRenderer.render(window);
        window.display();
    }
}
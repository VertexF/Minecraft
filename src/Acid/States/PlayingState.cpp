#include "PlayingState.h"

#include <glm/glm.hpp>

#include "../Renderer/RenderMaster.h"
#include "../Source/Application.h"
#include "../World/Chunk/ChunkMeshBuilder.h"

namespace acid 
{
    StatePlaying::StatePlaying(Application& app) :
        StateBase(app)
    {
        app.getCamera().hookEntity(_player);

        ChunkMeshBuilder builder(_chunkTest);
        builder.buildMesh(_chunkTest.mesh);

        _chunkTest.mesh.bufferMesh();
    }

    void StatePlaying::handleEvent(sf::Event e) 
    {
    }

    void StatePlaying::handleInput() 
    {
        _player.handleInput(_application->getWindow());
    }

    void StatePlaying::update(float deltaTime) 
    {
        _player.update(deltaTime);
    }

    void StatePlaying::render(RenderMaster& renderer) 
    {
        //renderer.drawCube({ -1.1, 0, -1.1 });
        renderer.drawChunk(_chunkTest.mesh);
    }
}
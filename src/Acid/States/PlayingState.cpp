#include "PlayingState.h"

#include <glm/glm.hpp>

#include "../Renderer/RenderMaster.h"
#include "../Source/Application.h"

namespace acid 
{
    StatePlaying::StatePlaying(Application& app) :
        StateBase(app)
    {
        app.getCamera().hookEntity(_player);
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
        renderer.drawQuad({ 0, 0, 0 });
    }
}
#include "PlayingState.h"

#include <glm/glm.hpp>

#include "../Renderer/RenderMaster.h"

namespace acid 
{
    StatePlaying::StatePlaying(Application& app) :
        StateBase(app)
    {
    }

    void StatePlaying::handleEvent(sf::Event e) 
    {
    }

    void StatePlaying::handleInput() 
    {
    }

    void StatePlaying::update(float deltaTime) 
    {
    }

    void StatePlaying::render(RenderMaster& renderer) 
    {
        static sf::Clock clock;
        static float lastTime = 0.f;
        float timeNow = clock.getElapsedTime().asSeconds();
        auto dt = timeNow - lastTime;
        lastTime = timeNow;

        renderer.drawQuad({0, 0, glm::sin(timeNow) * 3 });
    }
}
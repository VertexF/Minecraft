#include "PlayingState.h"

#include <glm/glm.hpp>

#include "../Renderer/RenderMaster.h"
#include "../Source/Application.h"
#include "../World/Chunk/ChunkMeshBuilder.h"
#include "../Source/Global.h"
#include "../Maths/Ray.h"

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

        static sf::Clock timer;
        glm::vec3 lastPosition;

        for (Ray ray(_player.position, _player.rotation); ray.getLenght() < 6; ray.step(0.1)) 
        {
            int x = ray.getEnd().x;
            int y = ray.getEnd().y;
            int z = ray.getEnd().z;

            auto block = WORLD.getBlock(x, y, z);

            if (block != 0) 
            {
                if (timer.getElapsedTime().asSeconds() > 0.2) 
                {
                    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) 
                    {
                        timer.restart();
                        WORLD.editBlock(x, y, z, 0);
                        break;
                    }
                    else if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
                    {
                        timer.restart();
                        WORLD.editBlock(lastPosition.x, lastPosition.y, lastPosition.z, 2);
                        break;
                    }
                }
            }

            lastPosition = ray.getEnd();
        }
    }

    void StatePlaying::update(float deltaTime) 
    {
        _player.update(deltaTime);
    }

    void StatePlaying::render(RenderMaster& renderer) 
    {
        WORLD.renderWorld(renderer);
    }
}
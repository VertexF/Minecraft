#include "PlayingState.h"

#include <stdexcept>

#include <glm/glm.hpp>

#include "../Renderer/RenderMaster.h"
#include "../Source/Application.h"
#include "../Source/Global.h"
#include "../Maths/Ray.h"
#include "../World/Event/PlayerDigEvent.h"
#include "../Source/Entity.h"

namespace acid 
{
    StatePlaying::StatePlaying(Application& app) :
        StateBase(app), _world(app.getCamera(), _player)
    {
        app.getCamera().hookEntity(_player);

        if (_crossHairTexture.loadFromFile("Assets/Textures/ch.png") == false) 
        {
            throw std::runtime_error("Could not load the cross hair texture.");
        }
        _crossHair.setTexture(&_crossHairTexture);
        _crossHair.setSize({22, 22});
        _crossHair.setOrigin({ _crossHair.getGlobalBounds().width / 2, _crossHair.getGlobalBounds().height / 2 });
        sf::Vector2f position(_application->getWindow().getSize().x / 2, _application->getWindow().getSize().y / 2);
        _crossHair.setPosition(position);

        _music.load("Assets/Audio/minecraft_song.ogg");
        _otherMusic.load("Assets/Audio/minecraft_song2.ogg");
        _block.load("Assets/Audio/block_place.ogg", true, false);
    }

    void StatePlaying::handleEvent(sf::Event e) 
    {
    }

    void StatePlaying::handleInput() 
    {
        _player.handleInput(_application->getWindow());

        static sf::Clock timer;
        glm::vec3 lastPosition(0.f, 0.f, 0.f);

        for (Ray ray(_player.position, _player.rotation); ray.getLenght() < 6; ray.step(0.1)) 
        {
            int x = ray.getEnd().x;
            int y = ray.getEnd().y;
            int z = ray.getEnd().z;

            auto block = _world.getBlock(x, y, z);
            auto id = static_cast<BlockID>(block.id);

            if (id != BlockID::AIR && id != BlockID::WATER) 
            {
                if (timer.getElapsedTime().asSeconds() > 0.2) 
                {
                    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) 
                    {
                        timer.restart();
                        _block.play();
                        _world.addEvent<PlayerDigEvent>(sf::Mouse::Left, ray.getEnd(), _player);
                        break;
                    }
                    else if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
                    {
                        timer.restart();
                        _world.addEvent<PlayerDigEvent>(sf::Mouse::Right, lastPosition, _player);
                        break;
                    }
                }
            }

            lastPosition = ray.getEnd();
        }
    }

    void StatePlaying::update(float deltaTime) 
    {
        if (_player.position.x < 0) 
        {
            _player.position.x = 0;
        }

        if (_player.position.z < 0) 
        {
            _player.position.z = 0;
        }

        _world.update(_application->getCamera());
        _player.update(deltaTime, _world);
        //_fpsCounter.update();

        if (RANDOM_GENERATOR.intInRange(0, 25000) == 5) 
        {
            if (_otherMusic.isPlaying() == false)
            {
                _music.play();
            }
        }

        if (RANDOM_GENERATOR.intInRange(0, 25000) == 6)
        {
            if (_music.isPlaying() == false)
            {
                _otherMusic.play();
            }
        }
    }

    void StatePlaying::render(RenderMaster& renderer) 
    {
        static Entity cubeTest({ 0, 150, 0 }, { 50, 70, 25 });

        renderer.drawSFML(_crossHair);
        //_fpsCounter.draw(renderer);
        //renderer.drawCube(cubeTest);
        _world.renderWorld(renderer, _application->getCamera());

        _player.draw(renderer);
    }

    void StatePlaying::onOpen()
    {
        _application->turnOffMouse();
    }
}
#include "Application.h"

#include <GL/glew.h>
#include <SFML/Graphics.hpp>

#include "../States/PlayingState.h"

namespace acid 
{
    Application::Application(std::string&& title) 
    {
        pushState<StatePlaying>(*this);
    }

    void Application::mainLoop()
    {
        sf::Clock dtTimer;

        while (_context.window.isOpen() && _states.empty() == false)
        {
            auto deltaTime = dtTimer.restart();
            auto& state = *_states.back();

            state.handleInput();
            _camera.update();
            state.update(deltaTime.asSeconds());
            state.render(_masterRenderer);
            _masterRenderer.finishRender(_context.window, _camera);

            handleEvents();
            if (_isPopState) 
            {
                _isPopState = false;
                _states.pop_back();
            }
        }
    }

    void Application::popState() 
    {
        _isPopState = true;
    }

    void Application::turnOffMouse() 
    {
        _context.window.setMouseCursorVisible(false);
    }

    void Application::turnOnMouse() 
    {
        _context.window.setMouseCursorVisible(true);
    }

    void Application::handleEvents() 
    {
        sf::Event e;
        while (_context.window.pollEvent(e)) 
        {
            switch (e.type) 
            {
            case sf::Event::Closed:
                _context.window.close();
                break;

            case sf::Event::KeyPressed:
                switch (e.key.code)
                {
                case sf::Keyboard::Escape:
                    _context.window.close();
                    break;

                default:
                    break;
                }
                break;

            default:
                break;
            }
        }
    }
}
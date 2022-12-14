#include "FPSCounter.h"

#include <stdexcept>

#include "../Renderer/RenderMaster.h"

namespace acid 
{
    FPSCounter::FPSCounter() 
    {
        _text.move({ 10, 10 });
        _text.setOutlineColor(sf::Color::Black);
        _text.setOutlineThickness(2);
        
        if(_font.loadFromFile("Assets/Fonts/rs.ttf") == false)
        {
            throw std::runtime_error("Could not load the TTF file.");
        }

        _text.setFont(_font);
        _text.setCharacterSize(25);
    }

    void FPSCounter::update() 
    {
        _frameCount++;
        if (_delayTimer.getElapsedTime().asSeconds() > 0.5) 
        {
            _fps = _frameCount / _fpsTimer.restart().asSeconds();

            _frameCount = 0;
            _delayTimer.restart();
        }
    }

    void FPSCounter::draw(RenderMaster& renderer) 
    {
        _text.setString("FPS: " + std::to_string(_fps));
        renderer.drawSFML(_text);
    }
}
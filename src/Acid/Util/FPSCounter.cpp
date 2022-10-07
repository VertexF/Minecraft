#include "FPSCounter.h"

namespace acid 
{
    FPSCounter::FPSCounter() 
    {
    }

    float FPSCounter::getFPS() const
    {
        return _fps;
    }

    void FPSCounter::update() 
    {
        _frameCount++;
        if (_delayTimer.getElapsedTime().asSeconds()) 
        {
            _fps *= _frameCount / _fpsTimer.restart().asMicroseconds() * 1000;

            _frameCount = 0;
            _delayTimer.restart();
        }
    }
}
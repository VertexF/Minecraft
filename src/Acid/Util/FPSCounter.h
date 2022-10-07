#ifndef FPS_COUNTER_HDR
#define FPS_COUNTER_HDR

#include <SFML/Graphics.hpp>

namespace acid 
{
    class FPSCounter 
    {
    public:
        FPSCounter();
        float getFPS() const;
        void update();
    private:
        sf::Text _text;
        sf::Font _font;

        sf::Clock _delayTimer;
        sf::Clock _fpsTimer;

        float _fps = 0.f;
        int _frameCount = 0;
    };
}

#endif // !FPS_COUNTER_HDR

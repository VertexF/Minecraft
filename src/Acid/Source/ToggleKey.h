#ifndef TOGGLE_KEY_HDR
#define TOGGLE_KEY_HDR

#include <SFML/Graphics.hpp>

namespace acid 
{
    class ToggleKey 
    {
    public:
        ToggleKey(sf::Keyboard::Key key);

        bool isKeyPressed();
    private:
        sf::Keyboard::Key _key;
        sf::Clock _delayTime;
    };
}

#endif // !TOGGLE_KEY_HDR

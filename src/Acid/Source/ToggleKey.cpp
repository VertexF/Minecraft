#include "ToggleKey.h"

namespace acid 
{
    ToggleKey::ToggleKey(sf::Keyboard::Key key) :
        _key(key)
    {
    }

    bool ToggleKey::isKeyPressed() 
    {
        if (_delayTime.getElapsedTime().asSeconds() > 0.2) 
        {
            if (sf::Keyboard::isKeyPressed(_key)) 
            {
                _delayTime.restart();
                return true;
            }
        }

        return false;
    }
}
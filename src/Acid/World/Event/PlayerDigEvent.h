#ifndef PLAYER_DIG_EVENT
#define PLAYER_DIG_EVENT

#include <GLM/glm.hpp>
#include <SFML/Graphics.hpp>

#include "IWorldEvent.h"


namespace acid 
{
    class Player;

    class PlayerDigEvent : public IWorldEvent
    {
    public:
        PlayerDigEvent(sf::Mouse::Button button, const glm::vec3& location, Player& player);
        PlayerDigEvent() = delete;
        virtual ~PlayerDigEvent() = default;

        void handle(World& world);
    private:
        void dig(World& world);

        sf::Mouse::Button _buttonPressed;
        glm::vec3 _digSpot;
        Player* _player;
    };
}

#endif // !PLAYER_DIG_EVENT

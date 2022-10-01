#ifndef PLAYER_HDR
#define PLAYER_HDR

#include <SFML/Graphics.hpp>

#include "../Source/Entity.h"

namespace acid 
{
    class Player : public Entity 
    {
    public:
        Player();

        void handleInput(const sf::RenderWindow& window);

        void update(float dt);
    private:
        void keyboardInput();
        void mouseInput(const sf::RenderWindow& window);

        glm::vec3 _velocity;
    };
}

#endif // !PLAYER_HDR

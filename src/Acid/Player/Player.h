#ifndef PLAYER_HDR
#define PLAYER_HDR

#include <SFML/Graphics.hpp>
#include <vector>

#include "../Source/Entity.h"
#include "../Item/ItemStack.h"
#include "../Item/Material.h"
#include "../Source/ToggleKey.h"

namespace acid 
{
    class World;
    class RenderMaster;

    class Player : public Entity 
    {
    public:
        Player();

        void handleInput(const sf::RenderWindow& window);

        void update(float dt, World& world);
        void collide(World& world, const glm::vec3& vel, float dt);

        void addItem(const Material& material);
        void draw(RenderMaster& master);

        ItemStack& getHelpItem();
    private:
        void keyboardInput();
        void mouseInput(const sf::RenderWindow& window);

        std::vector<ItemStack> _items;
        std::vector<sf::Text> _itemText;
        sf::Font font;

        ToggleKey _itemDown;
        ToggleKey _itemUp;

        bool _isOnGround;
        int _heldItem;
    };
}

#endif // !PLAYER_HDR

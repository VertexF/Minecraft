#ifndef PLAYER_HDR
#define PLAYER_HDR

#include <SFML/Graphics.hpp>
#include <vector>

#include "../Source/Entity.h"
#include "../Item/ItemStack.h"
#include "../Item/Material.h"
#include "../Source/ToggleKey.h"
#include "../Audio/SoundEffects.h"

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

        ItemStack& getHeldItem();
    private:
        void jump();

        void keyboardInput();
        void mouseInput(const sf::RenderWindow& window);

        std::vector<ItemStack> _items;
        std::vector<sf::Text> _itemText;
        sf::Font font;
        SoundEffects _grassWalkingSound;

        ToggleKey _itemDown;
        ToggleKey _itemUp;

        bool _isOnGround;
        bool _isFlying;
        bool _isWalking;
        int _heldItem;
        float _speed;

        glm::vec3 _acceleration;
    };
}

#endif // !PLAYER_HDR

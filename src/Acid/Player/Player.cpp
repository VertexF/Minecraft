#include "Player.h"

#include <stdexcept>

#include "../World/World.h"
#include "../Renderer/RenderMaster.h"

namespace acid 
{
    Player::Player() : _isOnGround(false),
        Entity({ 25.f, 125.f, 25.f }, { 0, 0, 0 }, {0.5, 1.5, 0.5}), _heldItem(0), _itemDown(sf::Keyboard::Down), _itemUp(sf::Keyboard::Up)
    {
        if (font.loadFromFile("Assets/Fonts/rs.ttf") == false)
        {
            throw std::runtime_error("Could not load TTF file.");
        }

        for (int i = 0; i < 5; i++) 
        {
            sf::Text text;
            text.setFont(font);
            text.setOutlineColor(sf::Color::Black);
            text.setCharacterSize(25);
            sf::Vector2f position( 20.f, 20.f * i + 100.f);
            text.setPosition(position);
            _itemText.push_back(text);
        }
    }

    void Player::handleInput(const sf::RenderWindow& window) 
    {
        keyboardInput();
        mouseInput(window);
    }

    void Player::update(float dt, World &world) 
    {
        //if (_isOnGround == false) 
        //{
        //    velocity.y -= 55 * dt;
        //}
        //_isOnGround = false;

        box.update(position);
        velocity.x *= 0.95;
        velocity.z *= 0.95;
        velocity.y *= 0.95;

        position.x += velocity.x * dt;
        //collide(world, { velocity.x, 0, 0 }, dt);

        position.y += velocity.y * dt;
        //collide(world, { 0, velocity.y, 0 }, dt);

        position.z += velocity.z * dt;
        //collide(world, { 0, 0, velocity.z }, dt);
    }

    void Player::collide(World& world, const glm::vec3& vel, float dt)
    {
        for (int x = position.x - position.x; x < position.x + box.dimension.x; x++)
        {
            for (int y = position.y - box.dimension.y; y < position.y + 0.7; y++)
            {
                for (int z = position.z - box.dimension.y; z < position.z + box.dimension.z; z++)
                {
                    auto block = world.getBlock(x, y, z);

                    if(block != 0)
                    {
                        if (vel.x > 0)
                        {
                            position.x = x - box.dimension.x;
                        }
                        if (vel.x < 0)
                        {
                            position.x = x + box.dimension.x + 1;
                        }

                        if (vel.y > 0)
                        {
                            position.y = y - box.dimension.y;
                            velocity.y = 0;
                        }
                        if (vel.y < 0)
                        {
                            position.y = y + box.dimension.y + 1;
                            velocity.y = 0;
                            _isOnGround = true;
                        }

                        if (vel.z > 0)
                        {
                            position.z = z - box.dimension.z;
                        }
                        if (vel.z < 0)
                        {
                            position.z = z + box.dimension.z + 1;
                        }
                    }
                }
            }
        }
    }

    void Player::addItem(const Material& material)
    {
        Material::ID id = material.id;

        for (int i = 0; i < _items.size(); i++)
        {
            if(_items[i].getMaterial().id == id)
            {
                int leftOver = _items[i].add(1);
            }
            else if (_items[i].getMaterial().id == Material::ID::NOTHING)
            {
                _items[i] = { material, 1 };
                return;
            }
        }
    }

    void Player::draw(RenderMaster& master)
    {
        for (int i = 0; i < _items.size(); i++)
        {
            sf::Text& text = _itemText[i];
            if (i == _heldItem) 
            {
                text.setFillColor(sf::Color::Red);
            }
            else 
            {
                text.setFillColor(sf::Color::Black);
            }
            text.setString(_item[i].getMaterial().name);
            master.drawSFML(text);
        }
    }

    ItemStack& Player::getHelpItem() 
    {
        return _items[_heldItem];
    }

    void Player::keyboardInput() 
    {
        glm::vec3 change(0.0);
        float speed = 0.8;

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) 
        {
            change.x += -glm::cos(glm::radians(rotation.y + 90)) * speed;
            change.z += -glm::sin(glm::radians(rotation.y + 90)) * speed;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        {
            change.x += glm::cos(glm::radians(rotation.y + 90)) * speed;
            change.z += glm::sin(glm::radians(rotation.y + 90)) * speed;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        {
            change.x += -glm::cos(glm::radians(rotation.y)) * speed;
            change.z += -glm::sin(glm::radians(rotation.y)) * speed;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        {
            change.x += glm::cos(glm::radians(rotation.y)) * speed;
            change.z += glm::sin(glm::radians(rotation.y)) * speed;
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) 
        {
            change.y += speed;
        }
        else if(sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
        {
            change.y -= 8;
        }

        velocity += change;
    }

    void Player::mouseInput(const sf::RenderWindow& window)
    {
        static auto const BOUND = 80;
        static auto lastMousePosition = sf::Mouse::getPosition(window);
        auto change = sf::Mouse::getPosition() - lastMousePosition;

        rotation.y += change.x * 0.05;
        rotation.x += change.y * 0.05;

        if (rotation.x > BOUND) 
        {
            rotation.x = BOUND;
        }
        else if (rotation.x < -BOUND)
        {
            rotation.x = -BOUND;
        }

        if (rotation.y > 360)
        {
            rotation.y = 0;
        }
        else if (rotation.y < 0)
        {
            rotation.y = 360;
        }

        auto cx = static_cast<int>(window.getSize().x / 2);
        auto cy = static_cast<int>(window.getSize().y / 2);

        sf::Mouse::setPosition({ cx, cy }, window);
        lastMousePosition = sf::Mouse::getPosition();
    }
}
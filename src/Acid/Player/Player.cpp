#include "Player.h"

#include <stdexcept>

#include "../World/World.h"
#include "../Renderer/RenderMaster.h"

namespace acid 
{
    Player::Player() : _isOnGround(false),
        Entity({ 1500.f, 125.f, 1500.f }, { 0, 0, 0 }, {0.5, 1.5, 0.5}), _heldItem(0), _itemDown(sf::Keyboard::Down), _itemUp(sf::Keyboard::Up), _speed(0.25f), _acceleration(0, 0, 0)
    {
        if (font.loadFromFile("Assets/Fonts/rs.ttf") == false)
        {
            throw std::runtime_error("Could not load TTF file.");
        }

        for (int i = 0; i < 5; i++) 
        {
            _items.emplace_back(Material::NOTHING_BLOCK, 0);
        }

        for (float i = 0.f; i < 5.f; i++) 
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

        if (_itemDown.isKeyPressed()) 
        {
            _heldItem++;
            if(_heldItem == _items.size())
            {
                _heldItem = 0;
            }
        }
        else if (_itemUp.isKeyPressed()) 
        {
            _heldItem--;
            if (_heldItem == -1) 
            {
                _heldItem = _items.size() - 1;
            }
        }
    }

    void Player::update(float dt, World &world) 
    {
        velocity += _acceleration;
        _acceleration = { 0, 0, 0 };

        if (_isOnGround == false) 
        {
            velocity.y -= 55 * dt;
        }
        _isOnGround = false;

        position.x += velocity.x * dt;
        collide(world, { velocity.x, 0, 0 }, dt);

        position.y += velocity.y * dt;
        collide(world, { 0, velocity.y, 0 }, dt);

        position.z += velocity.z * dt;
        collide(world, { 0, 0, velocity.z }, dt);

        box.update(position);
        velocity.x *= 0.95;
        velocity.z *= 0.95;
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
                        if (vel.y > 0)
                        {
                            position.y = y - box.dimension.y;
                            velocity.y = 0;
                        }
                        else if (vel.y < 0)
                        {
                            position.y = y + box.dimension.y + 1;
                            velocity.y = 0;
                            _isOnGround = true;
                        }

                        if (vel.x > 0)
                        {
                            //jump();
                            position.x = x - box.dimension.x;
                        }
                        else if (vel.x < 0)
                        {
                            //jump();
                            position.x = x + box.dimension.x + 1;
                        }

                        if (vel.z > 0)
                        {
                            //jump();
                            position.z = z - box.dimension.z;
                        }
                        else if (vel.z < 0)
                        {
                            //jump();
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

        for (unsigned int i = 0; i < _items.size(); i++)
        {
            if (_items[i].getMaterial().id == id)
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
        for (unsigned int i = 0; i < _items.size(); i++)
        {
            sf::Text& text = _itemText[i];
            if (i == static_cast<unsigned int>(_heldItem))
            {
                text.setFillColor(sf::Color::Red);
            }
            else 
            {
                text.setFillColor(sf::Color::Black);
            }
            text.setString(_items[i].getMaterial().name + " " + std::to_string(_items[i].getNumInStack()));
            master.drawSFML(text);
        }
    }

    ItemStack& Player::getHelpItem() 
    {
        return _items[_heldItem];
    }

    void Player::jump()
    {
        if (_isOnGround) 
        {
            _isOnGround = false;
            _acceleration.y += _speed * 50;
        }
    }

    void Player::keyboardInput() 
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) 
        {
            _acceleration.x += -glm::cos(glm::radians(rotation.y + 90)) * _speed;
            _acceleration.z += -glm::sin(glm::radians(rotation.y + 90)) * _speed;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        {
            _acceleration.x += glm::cos(glm::radians(rotation.y + 90)) * _speed;
            _acceleration.z += glm::sin(glm::radians(rotation.y + 90)) * _speed;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        {
            _acceleration.x += -glm::cos(glm::radians(rotation.y)) * _speed;
            _acceleration.z += -glm::sin(glm::radians(rotation.y)) * _speed;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        {
            _acceleration.x += glm::cos(glm::radians(rotation.y)) * _speed;
            _acceleration.z += glm::sin(glm::radians(rotation.y)) * _speed;
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) 
        {
            jump();
        }
        else if(sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
        {
            _acceleration.y -= _speed;
        }
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
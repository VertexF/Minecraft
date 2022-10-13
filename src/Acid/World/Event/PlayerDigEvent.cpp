#include "PlayerDigEvent.h"

#include "../World.h"
#include "../../Player/Player.h"
#include "../../Item/Material.h"

namespace acid 
{
    PlayerDigEvent::PlayerDigEvent(sf::Mouse::Button button, const glm::vec3& location, Player& player) :
        _buttonPressed(button), _digSpot(location), _player(&player)
    {
    }

    void PlayerDigEvent::handle(World& world) 
    {
        auto chunkLocation = World::getChunkXZ(_digSpot.x, _digSpot.z);
        if (world.getChunkManager().chunkLoadedAt(chunkLocation.x, chunkLocation.z)) 
        {
            dig(world);
        }
    }

    void PlayerDigEvent::dig(World& world) 
    {
        switch (_buttonPressed) 
        {
        case sf::Mouse::Button::Left: 
        {
            auto block = world.getBlock(_digSpot.x, _digSpot.y, _digSpot.z);
            const auto& material = Material::toMaterial(static_cast<BlockID>(block.id));
            _player->addItem(material);
            world.updateChunk(_digSpot.x, _digSpot.y, _digSpot.z);
            world.setBlock(_digSpot.x, _digSpot.y, _digSpot.z, 0);
            break;
        }
        case sf::Mouse::Button::Right:
        {
            auto& stack = _player->getHeldItem();
            auto& material = stack.getMaterial();
            if (material.id == Material::ID::NOTHING)
            {
                return;
            }
            else
            {
                stack.remove();
                world.updateChunk(_digSpot.x, _digSpot.y, _digSpot.z);
                world.setBlock(_digSpot.x, _digSpot.y, _digSpot.z, material.toBlockID());
                world.playBlockSound();
                break;
            }
        }
        default:
            break;
        }
    }
}
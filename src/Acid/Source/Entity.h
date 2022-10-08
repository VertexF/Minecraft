#ifndef ENTITY_HDR
#define ENTITY_HDR

#include <glm/glm.hpp>

#include "../Physics/AABB.h"

namespace acid 
{
    struct Entity 
    {
        Entity() : position({ 0, 0, 0 }), rotation({ 0, 0, 0 }), velocity({ 0, 0, 0 }), box({ 0, 0, 0 })
        {
        }

        Entity(const glm::vec3& pos, const glm::vec3& rot) :
            position(pos), rotation(rot), velocity({ 0, 0, 0 }), box({ 0, 0, 0 })
        {
        }

        Entity(const glm::vec3& pos, const glm::vec3& rot, const glm::vec3& box) :
            position(pos), rotation(rot), velocity({0, 0, 0}), box(box)
        {
        }

        glm::vec3 position;
        glm::vec3 rotation;
        glm::vec3 velocity;

        AABB box;
    };
}

#endif // !ENTITY_HDR

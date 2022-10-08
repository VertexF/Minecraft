#ifndef AABB_HDR
#define AABB_HDR

#include <glm/glm.hpp>

namespace acid 
{
    struct AABB 
    {
        AABB(const glm::vec3& dim) :
            dimension(dim), position({ 0.f, 0.f, 0.f })
        {
        }

        void update(const glm::vec3& location) 
        {
            position = location;
        }

        glm::vec3 position;
        const glm::vec3 dimension;
    };
}

#endif // !AABB_HDR

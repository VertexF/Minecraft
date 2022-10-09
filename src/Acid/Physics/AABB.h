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

        void update(const glm::vec3& location) noexcept
        {
            position = location;
        }

        glm::vec3 getVN(const glm::vec3& normal) const noexcept 
        {
            glm::vec3 res = position;
            if (normal.x < 0) 
            {
                res.x += dimension.x;
            }
            if (normal.y < 0)
            {
                res.y += dimension.y;
            }
            if (normal.z < 0)
            {
                res.z += dimension.z;
            }

            return res;
        }

        glm::vec3 getVP(const glm::vec3& normal) const noexcept
        {
            glm::vec3 res = position;
            if (normal.x > 0)
            {
                res.x += dimension.x;
            }
            if (normal.y > 0)
            {
                res.y += dimension.y;
            }
            if (normal.z > 0)
            {
                res.z += dimension.z;
            }

            return res;
        }

        glm::vec3 position;
        const glm::vec3 dimension;
    };
}

#endif // !AABB_HDR

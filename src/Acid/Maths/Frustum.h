#ifndef FRUSTUM_HDR
#define FRUSTUM_HDR

#include <array>
#include <glm/glm.hpp>

#include "../Physics/AABB.h"

namespace acid 
{
    enum Planes
    {
        NEAR,
        FAR,
        LEFT,
        RIGHT,
        TOP,
        BOTTOM
    };

    struct Plane 
    {
        Plane();
        float distanceToPoint(const glm::vec3& point) const;

        float distanceToOrigin;
        glm::vec3 normal;
    };

    class ViewFrustum 
    {
    public:
        void update(const glm::mat4& projectionViewMatrix) noexcept;

        bool isBoxInFrustum(const AABB& box) const noexcept
        {
            bool result = true;
            for (auto& plane : _planes)
            {
                if (plane.distanceToPoint(box.getVP(plane.normal)) < 0)
                {
                    return false;
                }
                else if (plane.distanceToPoint(box.getVN(plane.normal)) < 0)
                {
                    result = true;
                }
            }

            return result;
        }
    private:
        std::array<Plane, 6> _planes;
    };
}

#endif // !FRUSTUM_HDR

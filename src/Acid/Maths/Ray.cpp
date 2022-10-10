#include "Ray.h"

namespace acid 
{
    Ray::Ray(const glm::vec3& position, const glm::vec3& direction) :
        _rayStart(position), _rayEnd(position), _direction(direction)
    {
    }

    void Ray::step(float scale)
    {
        float yaw = glm::radians(_direction.y + 90);
        float pitch = glm::radians(_direction.x);

        auto& point = _rayEnd;

        point.x -= glm::cos(yaw) * scale;
        point.z -= glm::sin(yaw) * scale;

        point.y -= glm::tan(pitch) * scale;
    }

    const glm::vec3& Ray::getEnd() const
    {
        return _rayEnd;
    }

    float Ray::getLenght() const
    {
        return glm::distance(_rayStart, _rayEnd);
    }
}
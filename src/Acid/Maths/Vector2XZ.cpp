#include "Vector2XZ.h"

namespace acid
{
    bool operator==(const VectorXZ& lhs, const VectorXZ& rhs) noexcept
    {
        if (&rhs.z == nullptr || &rhs.x == nullptr || &rhs == nullptr)
        {
            return false;
        }

        return (lhs.x == rhs.x && lhs.z == rhs.z);
    }

    bool operator==(const sf::Vector3i& lhs, const sf::Vector3i& rhs) noexcept
    {
        return (lhs.x == rhs.x && lhs.y == rhs.y && lhs.z == rhs.z);
    }
}
#include "Vector2XZ.h"

namespace acid 
{
    bool operator==(const VectorXZ& lhs, const VectorXZ& rhs)
    {
        return (lhs.x == rhs.x && lhs.z == rhs.z);
    }
}
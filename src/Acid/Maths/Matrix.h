#ifndef MATRIX_HDR
#define MATRIX_HDR

#include <glm/glm.hpp>

#include "../Source/Camera.h"
#include "../Source/Entity.h"

namespace acid 
{
    glm::mat4 makeModelMatrix(const Entity& entity);
    glm::mat4 makeViewMatrix(const Camera& camera);
    glm::mat4 makeProjectionMatrix(float fov);
}

#endif // !MATRIX_HDR

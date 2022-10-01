#ifndef MATRIX_HDR
#define MATRIX_HDR

#include <glm/glm.hpp>

#include "../Source/Camera.h"

namespace acid 
{
    glm::mat4 makeModelMatrix(const glm::vec3& position, const glm::vec3& rotation);
    glm::mat4 makeViewMatrix(const Camera& camera);
    glm::mat4 makeProjectionMatrix(float fov);
}

#endif // !MATRIX_HDR

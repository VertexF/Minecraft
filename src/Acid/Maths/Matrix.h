#ifndef MATRIX_HDR
#define MATRIX_HDR

#include <glm/glm.hpp>

#include "../Source/Camera.h"

namespace acid 
{
    glm::mat4 makeViewMatrix(const Camera& camera);
    glm::mat4 makeProjectionMatrix(float fov);
}

#endif // !MATRIX_HDR

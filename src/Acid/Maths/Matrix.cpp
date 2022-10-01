#include "Matrix.h"

#include <glm/gtc/matrix_transform.hpp>

namespace acid 
{
    glm::mat4 makeModelMatrix(const Entity& entity) 
    {
        glm::mat4 matrix = glm::mat4(1.0);

        matrix = glm::rotate(matrix, glm::radians(entity.rotation.x), { 1, 0, 0 });
        matrix = glm::rotate(matrix, glm::radians(entity.rotation.y), { 0, 1, 0 });
        matrix = glm::rotate(matrix, glm::radians(entity.rotation.z), { 0, 0, 1 });

        matrix = glm::translate(matrix, entity.position);

        return matrix;
    }

    glm::mat4 makeViewMatrix(const Camera& camera) 
    {
        glm::mat4 matrix = glm::mat4(1.0);

        matrix = glm::rotate(matrix, glm::radians(camera.rotation.x), { 1, 0, 0 });
        matrix = glm::rotate(matrix, glm::radians(camera.rotation.y), { 0, 1, 0 });
        matrix = glm::rotate(matrix, glm::radians(camera.rotation.z), { 0, 0, 1 });

        matrix = glm::translate(matrix, camera.position);

        return matrix;
    }

    glm::mat4 makeProjectionMatrix(float fov) 
    {
        return glm::perspective(glm::radians(fov), 1280.f / 720.f, 0.1f, 1000.f);
    }
}
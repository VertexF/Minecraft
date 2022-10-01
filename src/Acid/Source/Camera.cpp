#include "Camera.h"

#include <glm/gtc/matrix_transform.hpp>

#include "../Maths/Matrix.h"

namespace acid 
{
    Camera::Camera() 
    {
        _projectionMatrix = makeProjectionMatrix(90);
    }

    void Camera::update() 
    {
        _viewMatrix = makeViewMatrix(*this);
        _projViewMatrix = _projectionMatrix * _viewMatrix;
    }

    const glm::mat4& Camera::getViewMatrix() const noexcept 
    {
        return _viewMatrix;
    }

    const glm::mat4& Camera::getProjMatrix() const noexcept 
    {
        return _projectionMatrix;
    }

    const glm::mat4& Camera::getProjectionViewMatrix() const noexcept 
    {
        return _projViewMatrix;
    }

    const glm::vec3& Camera::getPosition() const noexcept 
    {
        return _worldPosition;
    }

    const glm::vec3& Camera::getRotation() const noexcept 
    {
        return _rotation;
    }
}
#include "Camera.h"

#include <glm/gtc/matrix_transform.hpp>

#include "../Maths/Matrix.h"

namespace acid 
{
    Camera::Camera() : _entity(nullptr)
    {
        _projectionMatrix = makeProjectionMatrix(90);
        _viewMatrix = glm::mat4(1.0);
        _projViewMatrix = glm::mat4(1.0);

        position = { 0.f, 0.f, 0.f };
        rotation = { 0.f, 0.f, 0.f };
    }

    void Camera::hookEntity(const Entity& entity)
    {
        _entity = &entity;
    }

    void Camera::update() 
    {
        position = _entity->position;
        rotation = _entity->rotation;

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
}
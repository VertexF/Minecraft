#ifndef CAMERA_HDR
#define CAMERA_HDR

#include <glm/glm.hpp>

#include "../Maths/Frustum.h"
#include "Entity.h"

namespace acid 
{
    class Camera : public Entity
    {
    public:
        Camera() noexcept;
        void update() noexcept;
        void hookEntity(const Entity& entity) noexcept;

        const glm::mat4& getViewMatrix() const noexcept;
        const glm::mat4& getProjMatrix() const noexcept;
        const glm::mat4& getProjectionViewMatrix() const noexcept;

        const ViewFrustum& getViewFrustum() const noexcept;
    private:
        const Entity* _entity;

        ViewFrustum _viewFrustum;

        glm::mat4 _projectionMatrix;
        glm::mat4 _viewMatrix;
        glm::mat4 _projViewMatrix;
    };
}

#endif // !CAMERA_HDR

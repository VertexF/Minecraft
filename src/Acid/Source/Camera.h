#ifndef CAMERA_HDR
#define CAMERA_HDR

#include <glm/glm.hpp>

#include "Entity.h"

namespace acid 
{
    class Camera : public Entity
    {
    public:
        Camera();
        void update();
        void hookEntity(const Entity& entity);

        const glm::mat4& getViewMatrix() const noexcept;
        const glm::mat4& getProjMatrix() const noexcept;
        const glm::mat4& getProjectionViewMatrix() const noexcept;
    private:
        const Entity* _entity;

        glm::mat4 _projectionMatrix;
        glm::mat4 _viewMatrix;
        glm::mat4 _projViewMatrix;
    };
}

#endif // !CAMERA_HDR

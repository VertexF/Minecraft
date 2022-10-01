#ifndef CAMERA_HDR
#define CAMERA_HDR

#include <glm/glm.hpp>

namespace acid 
{
    class Camera 
    {
    public:
        Camera();
        void update();

        const glm::mat4& getViewMatrix() const noexcept;
        const glm::mat4& getProjMatrix() const noexcept;
        const glm::mat4& getProjectionViewMatrix() const noexcept;

        const glm::vec3& getPosition() const noexcept;
        const glm::vec3& getRotation() const noexcept;

    private:
        glm::vec3 _worldPosition;
        glm::vec3 _rotation;

        glm::mat4 _projectionMatrix;
        glm::mat4 _viewMatrix;
        glm::mat4 _projViewMatrix;
    };
}

#endif // !CAMERA_HDR

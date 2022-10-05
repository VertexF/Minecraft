#ifndef SKYBOX_SHADER_HDR
#define SKYBOX_SHADER_HDR

#include <glm/glm.hpp>

#include "Shader.h"

namespace acid 
{
    class SkyboxShader : public Shader
    {
    public:
        SkyboxShader();

        void loadViewMatrix(const glm::mat4& viewMatrix);
        void loadProjectionMatrix(const glm::mat4& projectionMatrix);

    private:
        void getUniforms() override;

        glm::mat4 _viewMatrix;
        glm::mat4 _projectionMatrix;

        GLuint _locationViewMatrix;
        GLuint _locationProjectionMatrix;
    };
}

#endif // !SKYBOX_SHADER_HDR

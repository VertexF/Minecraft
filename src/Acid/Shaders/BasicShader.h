#ifndef BASIC_SHADER_HDR
#define BASIC_SHADER_HDR

#include <GL/glew.h>

#include "Shader.h"

namespace acid 
{
    class BasicShader : public Shader
    {
    public:
        BasicShader(const std::string& vertexFile = "BasicVertex", const std::string& fragmentFile = "BasicFragment");

        void loadProjectionViewMatrix(const glm::mat4& pvMatrix);
    private:
        virtual void getUniforms() override;

        GLuint _locationProjectionViewMatrix;
    };
}

#endif // !BASIC_SHADER_HDR

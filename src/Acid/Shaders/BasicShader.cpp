#include "BasicShader.h"

namespace acid 
{
    BasicShader::BasicShader(const std::string& vertexFile, const std::string& fragmentFile) :
        Shader(vertexFile, fragmentFile)
    {
    }

    void BasicShader::loadProjectionViewMatrix(const glm::mat4& pvMatrix)
    {
        loadMatrix4(_locationProjectionViewMatrix, pvMatrix);
    }

    void BasicShader::getUniforms() 
    {
        _locationProjectionViewMatrix = glGetUniformLocation(_id, "projViewMat");
    }
}
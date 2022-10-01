#include "BasicShader.h"

namespace acid
{
    BasicShader::BasicShader(const std::string& vertexFile, const std::string& fragmentFile) :
        Shader(vertexFile, fragmentFile)
    {
        getUniforms();
    }

    void BasicShader::loadProjectionViewMatrix(const glm::mat4& pvMatrix)
    {
        loadMatrix4(_locationProjectionViewMatrix, pvMatrix);
    }

    void BasicShader::loadModelMatrix(const glm::mat4& modelMatrix)
    {
        loadMatrix4(_locationModelMatrix, modelMatrix);
    }

    void BasicShader::getUniforms() 
    {
        useProgram();
        _locationProjectionViewMatrix = glGetUniformLocation(_id, "projViewMat");
        _locationModelMatrix = glGetUniformLocation(_id, "modelMatrix");
    }
}
#include "SkyboxShader.h"

namespace acid 
{
    SkyboxShader::SkyboxShader() : Shader("SkyboxVertex", "SkyboxFragment") 
    {
        getUniforms();
    }

    void SkyboxShader::loadViewMatrix(const glm::mat4& viewMatrix)
    {
        _viewMatrix = viewMatrix;
        _viewMatrix[3][0] = 0;
        _viewMatrix[3][0] = 0;
        _viewMatrix[3][0] = 0;

        Shader::loadMatrix4(_locationViewMatrix, _viewMatrix);
    }

    void SkyboxShader::loadProjectionMatrix(const glm::mat4& projectionMatrix) 
    {
        Shader::loadMatrix4(_locationProjectionMatrix, projectionMatrix);
    }

    void SkyboxShader::getUniforms() 
    {
        _locationProjectionMatrix = glGetUniformLocation(_id, "ProjectionMatrix");
        _locationViewMatrix = glGetUniformLocation(_id, "viewMatrix");
    }
}
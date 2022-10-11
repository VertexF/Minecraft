#include "WaterShader.h"

namespace acid 
{
    WaterShader::WaterShader(const std::string& vertexFile, const std::string& fragmentFile) :
        BasicShader(vertexFile, fragmentFile)
    {
        getUniforms();
    }

    void WaterShader::addTime(float time)
    {
        Shader::loadFloat(time);
    }

    void WaterShader::getUniforms()
    {
        BasicShader::getUniforms();
        _locationTime = glGetUniformLocation(_id, "time");
    }
}
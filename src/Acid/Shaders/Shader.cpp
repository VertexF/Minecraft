#include "Shader.h"

#include "ShaderLoader.h"

#include <glm/gtc/type_ptr.hpp>

namespace acid 
{
    Shader::Shader(const std::string& vertexFile, const std::string& fragmentFile) :
        _id(loadShaders(vertexFile, fragmentFile))
    {
        useProgram();
    }

    Shader::~Shader() 
    {
        glDeleteProgram(_id);
    }

    void Shader::useProgram() 
    {
        glUseProgram(_id);
    }

    void Shader::loadInt(GLuint location, int value) 
    {
        glUniform1i(location, value);
    }

    void Shader::loadFloat(GLuint location, int value) 
    {
        glUniform1f(location, value);
    }

    void Shader::loadVertex2(GLuint location, const glm::vec2& vect) 
    {
        glUniform2f(location, vect.x, vect.y);
    }

    void Shader::loadVertex3(GLuint location, const glm::vec3& vect) 
    {
        glUniform3f(location, vect.x, vect.y, vect.z);
    }

    void Shader::loadVertex4(GLuint location, const glm::vec4& vect) 
    {
        glUniform4f(location, vect.x, vect.y, vect.z, vect.w);
    }

    void Shader::loadMatrix4(GLuint location, const glm::mat4& matrix) 
    {
        glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
    }
}
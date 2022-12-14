#include "ShaderLoader.h"

#include "../Util/FileUtil.h"

#include <GL/glew.h>
#include <stdexcept>

namespace 
{
    GLuint compileShader(const GLchar* source, GLenum shaderType) 
    {
        auto shaderID = glCreateShader(shaderType);

        glShaderSource(shaderID, 1, &source, nullptr);
        glCompileShader(shaderID);

        GLint success = false;
        GLchar infoLog[512];

        glGetShaderiv(shaderID, GL_COMPILE_STATUS, &success);
        if (success == 0) 
        {
            glGetShaderInfoLog(shaderID, 512, nullptr, infoLog);
            throw std::runtime_error("Unable to load a shader: " + std::string(infoLog));
        }

        return shaderID;
    }

    GLuint linkProgram(GLuint vertexShaderID, GLuint fragmentShaderID) 
    {
        auto id = glCreateProgram();

        glAttachShader(id, vertexShaderID);
        glAttachShader(id, fragmentShaderID);

        glLinkProgram(id);

        return id;
    }
}

namespace acid 
{
    GLuint loadShaders(const std::string& vertexShader, const std::string& fragmentShader) 
    {
        auto vertexSource = getFileContents("Assets/Shaders/" + vertexShader + ".glsl");
        auto fragmentSource = getFileContents("Assets/Shaders/" + fragmentShader + ".glsl");

        auto vertexShaderID = compileShader(vertexSource.c_str(), GL_VERTEX_SHADER);
        auto fragmentShaderID = compileShader(fragmentSource.c_str(), GL_FRAGMENT_SHADER);

        auto shaderID = linkProgram(vertexShaderID, fragmentShaderID);

        glDeleteShader(vertexShaderID);
        glDeleteShader(fragmentShaderID);

        return shaderID;
    }
}
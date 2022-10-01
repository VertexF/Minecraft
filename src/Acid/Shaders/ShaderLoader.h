#ifndef SHADER_LOADER_HDR
#define SHADER_LOADER_HDR

#include <string>
#include <GL/glew.h>

namespace acid 
{
    GLuint loadShaders(const std::string& vertexShader, const std::string& fragmentShader);
}

#endif // !SHADER_LOADER_HDR

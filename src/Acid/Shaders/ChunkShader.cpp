#include "ChunkShader.h"

namespace acid 
{
    ChunkShader::ChunkShader(const std::string& vertexFile, const std::string& fragmentFile) :
        BasicShader(vertexFile, fragmentFile)
    {
        getUniforms();
    }

    void ChunkShader::getUniforms()
    {
        BasicShader::getUniforms();
    }
}
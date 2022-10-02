#ifndef CHUNK_SHADER_HDR
#define CHUNK_SHADER_HDR

#include <string>

#include "BasicShader.h"

namespace acid 
{
    class ChunkShader : public BasicShader
    {
    public:
        ChunkShader(const std::string& vertexFile = "ChunkVertex", const std::string& fragmentFile = "ChunkFragment");

    private:
        void getUniforms() override;
    };
}

#endif // !CHUNK_SHADER_HDR

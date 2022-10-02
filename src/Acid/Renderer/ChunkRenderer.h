#ifndef CHUNK_RENDERER_HDR
#define CHUNK_RENDERER_HDR

#include <vector>

#include "../Shaders/ChunkShader.h"

namespace acid 
{
    class ChunkMesh;
    class Camera;

    class ChunkRenderer 
    {
    public:
        void add(const ChunkMesh& mesh);
        void render(const Camera& camera);
    private:
        std::vector<const ChunkMesh* > _chunks;
        ChunkShader _shader;
    };
}

#endif // !CHUNK_RENDERER_HDR

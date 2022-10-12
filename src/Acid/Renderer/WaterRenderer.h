#ifndef WATER_RENDERER_HDR
#define WATER_RENDERER_HDR

#include <vector>
#include <SFML/Graphics.hpp>

#include "../Shaders/ChunkShader.h"

namespace acid 
{
    class ChunkMesh;
    class Camera;

    class WaterRenderer
    {
    public:
        void add(const ChunkMesh& mesh);
        void render(const Camera& camera);
    private:
        sf::Clock _timer;

        std::vector<const ChunkMesh* > _chunks;
        ChunkShader _shader;
    };
}

#endif // !WATER_RENDERER_HDR

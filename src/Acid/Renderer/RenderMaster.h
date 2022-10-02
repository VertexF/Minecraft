#ifndef RENDER_MASTER_HDR
#define RENDER_MASTER_HDR

#include <SFML/Graphics.hpp>
#include <glm/glm.hpp>

#include "QuadRenderer.h"
#include "CubeRenderer.h"
#include "ChunkRenderer.h"

namespace acid 
{
    class Camera;
    class ChunkMesh;
    class RenderMaster 
    {
    public:
        void drawQuad(const glm::vec3& pos);
        void drawCube(const glm::vec3& pos);
        void drawChunk(const ChunkMesh& mesh);

        void finishRender(sf::RenderWindow& window, const Camera& camera);
    private:
        QuadRenderer _quadRenderer;
        CubeRenderer _cubeRenderer;
        ChunkRenderer _chunkRenderer;
    };
}

#endif // !RENDER_MASTER_HDR

#ifndef RENDER_MASTER_HDR
#define RENDER_MASTER_HDR

#include <SFML/Graphics.hpp>
#include <glm/glm.hpp>

#include "QuadRenderer.h"
#include "CubeRenderer.h"
#include "ChunkRenderer.h"
#include "SkyboxRenderer.h"

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
        void drawSky();

        void finishRender(sf::RenderWindow& window, const Camera& camera);
    private:
        QuadRenderer _quadRenderer;
        CubeRenderer _cubeRenderer;
        ChunkRenderer _chunkRenderer;
        SkyRenderer _skyRenderer;

        bool _drawSky;
    };
}

#endif // !RENDER_MASTER_HDR

#ifndef RENDER_MASTER_HDR
#define RENDER_MASTER_HDR

#include <SFML/Graphics.hpp>
#include <glm/glm.hpp>

#include "QuadRenderer.h"
#include "CubeRenderer.h"
#include "ChunkRenderer.h"
#include "SkyboxRenderer.h"
#include "WaterRenderer.h"
#include "SFMLRenderer.h"

namespace acid 
{
    class Camera;
    class ChunkSection;
    struct Entity;
    class RenderMaster 
    {
    public:
        void drawQuad(const glm::vec3& pos);
        void drawCube(const Entity& entity);
        void drawChunk(const ChunkSection& chunk);
        void drawSFML(const sf::Drawable& drawable);
        void drawSky();

        void finishRender(sf::RenderWindow& window, const Camera& camera);
    private:
        QuadRenderer _quadRenderer;
        CubeRenderer _cubeRenderer;
        ChunkRenderer _chunkRenderer;
        SkyRenderer _skyRenderer;
        WaterRenderer _waterRender;
        SFMLRenderer _sfmlRenderer;

        bool _drawSky;
    };
}

#endif // !RENDER_MASTER_HDR

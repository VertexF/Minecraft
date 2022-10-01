#ifndef RENDER_MASTER_HDR
#define RENDER_MASTER_HDR

#include <SFML/Graphics.hpp>
#include <glm/glm.hpp>

#include "QuadRenderer.h"
#include "CubeRenderer.h"

namespace acid 
{
    class Camera;
    class RenderMaster 
    {
    public:
        void drawQuad(const glm::vec3& pos);
        void drawCube(const glm::vec3& pos);

        void finishRender(sf::RenderWindow& window, const Camera& camera);
    private:
        QuadRenderer _quadRenderer;
        CubeRenderer _cubeRenderer;
    };
}

#endif // !RENDER_MASTER_HDR

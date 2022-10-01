#ifndef RENDER_MASTER_HDR
#define RENDER_MASTER_HDR

#include "QuadRenderer.h"

#include <SFML/Graphics.hpp>
#include <glm/glm.hpp>

namespace acid 
{
    class Camera;
    class RenderMaster 
    {
    public:
        void drawQuad(const glm::vec3& pos);

        void finishRender(sf::RenderWindow& window, const Camera& camera);
    private:
        QuadRenderer _quadRenderer;
    };
}

#endif // !RENDER_MASTER_HDR

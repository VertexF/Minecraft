#include "SFMLRenderer.h"

#include <GL/glew.h>

namespace acid 
{
    void SFMLRenderer::add(const sf::Drawable& drawable) 
    {
        _drawCalls.push_back(&drawable);
    }

    void SFMLRenderer::render(sf::RenderWindow& window) 
    {
        if (_drawCalls.empty()) 
        {
            return;
        }

        glDisable(GL_DEPTH_TEST);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
        glBindTexture(GL_TEXTURE_2D, 0);
        glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
        glUseProgram(0);

        window.pushGLStates();
        window.resetGLStates();

        for (const auto& draw : _drawCalls) 
        {
            window.draw(*draw);
        }

        window.popGLStates();
        _drawCalls.clear();
    }
}
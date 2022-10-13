#include "Context.h"

#include <GL/glew.h>
#include <stdexcept>

namespace acid 
{
    Context::Context()
    {
        sf::ContextSettings settings;
        settings.antialiasingLevel = 0;
        settings.majorVersion = 4;
        settings.minorVersion = 5;
        settings.depthBits = 24;
        settings.stencilBits = 8;

        sf::VideoMode videoMode;
        videoMode.size = { 1280, 720 };
        window.create(videoMode, "Minecraft", sf::Style::Fullscreen, settings);

        // Make the window the active window for OpenGL calls
        if (window.setActive(true) == false)
        {
            throw std::runtime_error("Failed to set window to active");
        }

        int width = window.getSize().x;
        int height = window.getSize().y;

        glewExperimental = GL_TRUE;
        glewInit();
        glViewport(0, 0, width, height);

        glCullFace(GL_BACK);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        //window.setFramerateLimit(90);
        window.setVerticalSyncEnabled(true);
    }
}
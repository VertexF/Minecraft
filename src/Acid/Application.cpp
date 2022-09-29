#include "Application.h"

#include <GL/glew.h>
#include <SFML/Graphics.hpp>

namespace acid 
{
    Application::Application() 
    {
        bool sRgb = false;

        sf::ContextSettings contextSettings;
        contextSettings.depthBits = 24;
        contextSettings.sRgbCapable = sRgb;
    }
}
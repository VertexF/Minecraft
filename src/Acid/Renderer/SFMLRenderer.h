#ifndef SFML_RENDERER_HDR
#define SFML_RENDERER_HDR

#include <vector>

#include <SFML/Graphics.hpp>

namespace acid 
{
    class SFMLRenderer 
    {
    public:
        void add(const sf::Drawable& drawable);
        void render(sf::RenderWindow& window);
    private:
        std::vector<const sf::Drawable*> _drawCalls;
    };
}

#endif // !SFML_RENDERER_HDR

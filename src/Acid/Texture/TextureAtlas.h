#ifndef TEXTURE_ATLAS
#define TEXTURE_ATLAS

#include <string>
#include <vector>

#include <GL/glew.h>
#include <SFML/Graphics.hpp>

#include "BasicTexture.h"

namespace acid 
{
    class TextureAtlas : public BasicTexture 
    {
    public:
        TextureAtlas(const std::string& textureFileName);

        std::vector<GLfloat> getTexture(const sf::Vector2i& coords);

    private:
        int _imageSize;
        int _indivitualTextureSize;
    };
}

#endif // !TEXTURE_ATLAS

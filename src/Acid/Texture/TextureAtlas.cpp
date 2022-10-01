#include "TextureAtlas.h"

#include <stdexcept>

#include <SFML/Graphics.hpp>

namespace acid
{
    TextureAtlas::TextureAtlas(const std::string& textureFileName)
    {
        sf::Image image;
        if (image.loadFromFile("Assets/Textures/" + textureFileName + ".png") == false)
        {
            throw std::runtime_error("Unable to open image: " + textureFileName);
        }
        loadFromImage(image);

        _imageSize = 256;
        _indivitualTextureSize = 16;
    }

    std::vector<GLfloat> TextureAtlas::getTexture(const sf::Vector2i& coords)
    {
        static const GLfloat TEX_PER_ROW = static_cast<GLfloat>(_imageSize) / static_cast<GLfloat>(_indivitualTextureSize);
        static const GLfloat INDV_TEX_SIZE = 1.f / TEX_PER_ROW;
        static const GLfloat PIXEL_SIZE = 1.f / static_cast<float>(_imageSize);

        GLfloat xMin = (coords.x * INDV_TEX_SIZE) + 0.5f * PIXEL_SIZE;
        GLfloat yMin = (coords.y * INDV_TEX_SIZE) + 0.5f * PIXEL_SIZE;

        GLfloat xMax = (xMin + INDV_TEX_SIZE) - 0.5f * PIXEL_SIZE;
        GLfloat yMax = (yMin + INDV_TEX_SIZE) - 0.5f * PIXEL_SIZE;

        return
        {
            xMax, yMax,
            xMin, yMax,
            xMin, yMin,
            xMax, yMin
        };
    }
}
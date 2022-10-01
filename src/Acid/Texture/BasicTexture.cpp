#include "BasicTexture.h"

#include <stdexcept>

namespace acid 
{
    BasicTexture::BasicTexture(const std::string& file) 
    {
        loadFromFile(file);
    }

    BasicTexture::~BasicTexture() 
    {
        glDeleteTextures(1, &_id);
    }

    void BasicTexture::loadFromFile(const std::string& file) 
    {
        sf::Image image;
        if (image.loadFromFile("Assets/Textures/" + file + ".png") == false)
        {
            std::string filePath = "Assets/Textures/" + file + ".png";
            throw std::runtime_error("Cound not load the file : " + filePath);
        }
        loadFromImage(image);
    }

    void BasicTexture::loadFromImage(const sf::Image& image)
    {
        glGenTextures(1, &_id);
        glBindTexture(GL_TEXTURE_2D, _id);

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image.getSize().x, image.getSize().y, 0, GL_RGBA, GL_UNSIGNED_BYTE, image.getPixelsPtr());

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    }

    void BasicTexture::bindTexture() const 
    {
        glBindTexture(GL_TEXTURE_2D, _id);
    }
}
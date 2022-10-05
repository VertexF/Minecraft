#ifndef CUBE_TEXTURE_HDR
#define CUBE_TEXTURE_HDR

#include <GL/glew.h>
#include <array>
#include <string>
#include <SFML/Graphics.hpp>

namespace acid 
{
    class CubeTexture 
    {
    public:
        CubeTexture() = default;
        CubeTexture(const std::array<std::string, 6>& files);

        ~CubeTexture();

        void loadFromFile(const std::array<std::string, 6>& files);

        void bindTexture() const;
    private:
        GLuint _textureID;
    };
}

#endif // !CUBE_TEXTURE_HDR

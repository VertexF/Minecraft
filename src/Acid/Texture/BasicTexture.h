#ifndef BASIC_TEXTURE_HDR
#define BASIC_TEXTURE_HDR

#include <GL/glew.h>
#include <string>

#include "../Util/NonCopyable.h"

namespace acid 
{
    class BasicTexture 
    {
    public:
        BasicTexture() = default;
        BasicTexture(const std::string& file);
        ~BasicTexture();

        void loadFromFile(const std::string& file);
        void bindTexture() const;

    private:
        GLuint _id;
    };
}

#endif // !BASIC_TEXTURE_HDR

#include "GLFunctions.h"

namespace acid 
{
    void drawElements(GLuint indicesCount) noexcept
    {
        glDrawElements(GL_TRIANGLES, indicesCount, GL_UNSIGNED_INT, nullptr);
    }
}
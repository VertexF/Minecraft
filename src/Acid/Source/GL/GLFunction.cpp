#include "GLFunctions.h"

namespace acid 
{
    void drawElements(GLuint indicesCount) 
    {
        glDrawElements(GL_TRIANGLES, indicesCount, GL_UNSIGNED_INT, nullptr);
    }
}
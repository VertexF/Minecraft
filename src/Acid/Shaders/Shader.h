#ifndef SHADER_HDR
#define SHADER_HDR

#include <string>
#include <GL/glew.h>
#include <glm/glm.hpp>

#include "../Util/NonCopyable.h"

namespace acid 
{
    //Does this need to be noncopyable?
    class Shader : public NonCopyable 
    {
    public:
        Shader(const std::string& vertexFile, const std::string& fragmentFile);
        virtual ~Shader();

        void useProgram();

        void loadInt(GLuint location, int value);
        void loadFloat(GLuint location, int value);

        void loadVertex2(GLuint location, const glm::vec2& vect);
        void loadVertex3(GLuint location, const glm::vec3& vect);
        void loadVertex4(GLuint location, const glm::vec4& vect);

        void loadMatrix4(GLuint location, const glm::mat4& matrix);
    protected:
        virtual void getUniforms() = 0;
        GLuint _id;
    };
}

#endif // !SHADER_HDR

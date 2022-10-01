#ifndef MODEL_HDR
#define MODEL_HDR

#include <GL/glew.h>
#include <vector>
#include <string>

#include "../Util/NonCopyable.h"

namespace acid 
{
    class Model : public NonCopyable
    {
    public:
        Model() = default;
        Model(const std::vector<GLfloat>& vertexPosition, const std::vector<GLfloat>& textureCoords, const std::vector<GLuint>& indices);
        virtual ~Model();

        void addData(const std::vector<GLfloat>& vertexPosition, const std::vector<GLfloat>& textureCoords, const std::vector<GLuint>& indices);

        void deleteData();
        void addVBO(int dimensions, const std::vector<GLfloat>& data);
        void bindVAO() const;

        int getIndicesCount() const;

    private:
        void addEBO(const std::vector<GLuint>& indices);

        GLuint _vao = 0;
        int _vboCount = 0;
        int _indicesCount = 0;
        std::vector<GLuint> _buffers;
    };
}

#endif // !MODEL_HDR

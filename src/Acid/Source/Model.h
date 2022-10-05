#ifndef MODEL_HDR
#define MODEL_HDR

#include <GL/glew.h>
#include <vector>
#include <string>

#include "Mesh.h"

namespace acid 
{
    class Model
    {
    public:
        Model() = default;
        Model(const Mesh& mesh);
        virtual ~Model();

        Model(Model&& other) noexcept;
        Model& operator=(Model&& other) noexcept;
        Model(const Model& other);
        Model& operator=(const Model& other);

        void addData(const Mesh& mesh);

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

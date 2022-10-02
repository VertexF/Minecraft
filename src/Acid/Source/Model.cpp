#include "Model.h"

namespace acid 
{
    Model::Model(const Mesh& mesh) 
    {
        addData(mesh);
    }

    Model::~Model() 
    {
        deleteData();
    }

    void Model::addData(const Mesh& mesh) 
    {
        if (_vao != 0) 
        {
            deleteData();
        }

        _indicesCount = mesh.indices.size();

        glGenVertexArrays(1, &_vao);
        glBindVertexArray(_vao);

        addVBO(3, mesh.vertexPosition);
        addVBO(2, mesh.textureCoords);
        addEBO(mesh.indices);
    }

    void Model::deleteData() 
    {
        glDeleteVertexArrays(1, &_vao);
        glDeleteBuffers(_buffers.size(), _buffers.data());

        _buffers.clear();

        _vboCount = 0;
        _vao = 0;
        _indicesCount = 0;
    }

    void Model::addVBO(int dimensions, const std::vector<GLfloat>& data) 
    {
        GLuint vbo;
        glGenBuffers(1, &vbo);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(GLfloat), data.data(), GL_STATIC_DRAW);

        glVertexAttribPointer(_vboCount, dimensions, GL_FLOAT, GL_FALSE, 0, (GLvoid *)0);
        glEnableVertexAttribArray(_vboCount++);

        _buffers.push_back(vbo);
    }

    void Model::bindVAO() const 
    {
        glBindVertexArray(_vao);
    }

    int Model::getIndicesCount() const 
    {
        return _indicesCount;
    }

    void Model::addEBO(const std::vector<GLuint>& indices) 
    {
        GLuint ebo;
        glGenBuffers(1, &ebo);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), indices.data(), GL_STATIC_DRAW);
    }
}
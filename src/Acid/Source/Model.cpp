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

    Model::Model(Model&& other) noexcept :
        _vao(other._vao), _vboCount(other._vboCount), _indicesCount(other._indicesCount),
        _buffers(std::move(other._buffers))
    {
    }

    Model& Model::operator=(Model&& other) noexcept
    {
        _vao = other._vao;
        _vboCount = other._vboCount;
        _indicesCount = other._indicesCount;
        _buffers = std::move(other._buffers);

        other._vao = 0;
        other._vboCount = 0;
        other._indicesCount = 0;

        return *this;
    }

    Model::Model(const Model& other)
    {
        for (int i = 0; i < other._buffers.size(); i++)
        {
            _buffers.push_back(other._buffers.at(i));
        }

        _vao = other._vao;
        _vboCount = other._vboCount;
        _indicesCount = other._indicesCount;
    }

    Model& Model::operator=(const Model& other)
    {
        for (int i = 0; i < other._buffers.size(); i++)
        {
            _buffers.push_back(other._buffers.at(i));
        }

        _vao = other._vao;
        _vboCount = other._vboCount;
        _indicesCount = other._indicesCount;

        return *this;
    }

    void Model::addData(const Mesh& mesh) 
    {
        genVAO();
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

    void Model::genVAO() 
    {
        if (_vao != 0)
        {
            deleteData();
        }

        glGenVertexArrays(1, &_vao);
        glBindVertexArray(_vao);
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
        _indicesCount = indices.size();
        GLuint ebo;
        glGenBuffers(1, &ebo);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), indices.data(), GL_STATIC_DRAW);
    }
}
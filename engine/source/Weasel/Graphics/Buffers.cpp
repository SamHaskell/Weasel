#include "Weasel/Graphics/Buffers.hpp"

namespace Weasel {
    VertexBuffer::VertexBuffer() {
        glGenBuffers(1, &BufferID);
    }

    VertexBuffer::~VertexBuffer() {
        glDeleteBuffers(1, &BufferID);
    }

    void VertexBuffer::SetData(const std::vector<Vertex>& vertices) {
        glBindBuffer(GL_ARRAY_BUFFER, BufferID);
        glBufferData(
            GL_ARRAY_BUFFER,
            sizeof(Vertex) * static_cast<u32>(vertices.size()),
            vertices.data(),
            GL_STATIC_DRAW
        );
        VertexCount = static_cast<u32>(vertices.size());
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

    IndexBuffer::IndexBuffer() {
        glGenBuffers(1, &BufferID);
    }

    IndexBuffer::~IndexBuffer() {
        glDeleteBuffers(1, &BufferID);
    }

    void IndexBuffer::SetData(const std::vector<Index>& indices) {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, BufferID);
        glBufferData(
            GL_ELEMENT_ARRAY_BUFFER,
            sizeof(Index) * static_cast<u32>(indices.size()),
            indices.data(),
            GL_STATIC_DRAW
        );
        IndexCount = static_cast<u32>(indices.size());
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }

    VertexArrayObject::VertexArrayObject() {
        glGenVertexArrays(1, &VertexArrayID);
    }

    VertexArrayObject::~VertexArrayObject() {
        glDeleteVertexArrays(1, &VertexArrayID);
    }

    void VertexArrayObject::SetBindings(VertexBuffer& vertexBuffer, IndexBuffer& indexBuffer) {
        Bind();
        vertexBuffer.Bind();
        indexBuffer.Bind();

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Position));
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Normal));
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Color));
        glEnableVertexAttribArray(2);
        glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, TexCoord));
        glEnableVertexAttribArray(3);        

        Unbind();
        vertexBuffer.Unbind();
        indexBuffer.Unbind();
    }
}
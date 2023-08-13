#pragma once

#include "Weasel/Graphics/RenderUtils.hpp"

namespace Weasel {
    struct VertexBuffer {
        VertexBuffer();
        ~VertexBuffer();
        inline void Bind() { glBindBuffer(GL_ARRAY_BUFFER, BufferID); }
        inline void Unbind() { glBindBuffer(GL_ARRAY_BUFFER, 0); }
        void SetData(const std::vector<Vertex>& vertices);
        u32 BufferID = 0;
        u32 VertexCount = 0;
    };

    struct IndexBuffer {
        IndexBuffer();
        ~IndexBuffer();
        inline void Bind() { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, BufferID); }
        inline void Unbind() { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); }
        void SetData(const std::vector<Index>& indices);
        u32 BufferID = 0;
        u32 IndexCount = 0;
    };

    struct VertexArrayObject {
        VertexArrayObject();
        ~VertexArrayObject();
        inline void Bind() { glBindVertexArray(VertexArrayID); }
        inline void Unbind() { glBindVertexArray(0); }
        void SetBindings(VertexBuffer& vertexBuffer, IndexBuffer& indexBuffer);
        u32 VertexArrayID = 0;
    };
}
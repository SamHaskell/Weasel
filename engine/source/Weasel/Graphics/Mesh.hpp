#pragma once

#include "Weasel/Graphics/RenderUtils.hpp"
#include "Weasel/Graphics/Buffers.hpp"

namespace Weasel {
    class Mesh {
        public:
            static std::shared_ptr<Mesh> Create(const std::vector<Vertex>& vertices, const std::vector<Index>& indices);
            Mesh(const std::vector<Vertex>& vertices, const std::vector<Index>& indices);
            ~Mesh();
            Mesh(const Mesh&) = delete;
            Mesh &operator=(const Mesh&) = delete;

            void Draw();

            std::vector<Vertex> Vertices;
            std::vector<Index> Indices;
        private:
            VertexBuffer m_VertexBuffer;
            IndexBuffer m_IndexBuffer;
            VertexArrayObject m_VertexArrayObject;
    };
}
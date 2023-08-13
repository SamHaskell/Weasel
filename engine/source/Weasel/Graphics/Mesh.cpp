#include "Weasel/Graphics/Mesh.hpp"

namespace Weasel
{
    std::shared_ptr<Mesh> Mesh::Create(std::vector<Vertex> vertices, std::vector<Index> indices)
    {
        return std::make_shared<Mesh>(vertices, indices);
    }

    Mesh::Mesh(const std::vector<Vertex>& vertices, const std::vector<Index>& indices)
    {
        Vertices = vertices;
        Indices = indices;
        m_VertexBuffer.SetData(Vertices);
        m_IndexBuffer.SetData(Indices);
        m_VertexArrayObject.SetBindings(m_VertexBuffer, m_IndexBuffer);
    }

    Mesh::~Mesh()
    {

    }

    void Mesh::Draw()
    {
        m_VertexArrayObject.Bind();
        glDrawElements(GL_TRIANGLES, m_IndexBuffer.IndexCount, GL_UNSIGNED_INT, 0);
        m_VertexArrayObject.Unbind();
    }
}
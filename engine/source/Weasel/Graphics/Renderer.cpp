#include "Weasel/Graphics/Renderer.hpp"

namespace Weasel {
    std::unique_ptr<Renderer> Renderer::Create() {
        return std::make_unique<Renderer>();
    }

    Renderer::Renderer() {

    }

    Renderer::~Renderer() {

    }

    void Renderer::BeginScene(std::shared_ptr<Camera> camera) {
        m_Camera = camera;
    }

    void Renderer::EndScene() {

    }

    void Renderer::DrawMesh(const std::shared_ptr<Mesh> mesh, const std::shared_ptr<Material> material) {
        mesh->Draw();
    }
}
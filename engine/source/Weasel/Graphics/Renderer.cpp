#include "Weasel/Graphics/Renderer.hpp"

namespace Weasel {
    std::unique_ptr<Renderer> Renderer::Create() {
        return std::make_unique<Renderer>();
    }

    Renderer::Renderer() {

    }

    Renderer::~Renderer() {

    }
}
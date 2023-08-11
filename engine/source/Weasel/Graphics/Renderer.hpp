#pragma once

#include "Weasel/Graphics/RenderUtils.hpp"

namespace Weasel {
    class Renderer {
        public:
            static std::unique_ptr<Renderer> Create();
            Renderer();
            ~Renderer();
            Renderer(const Renderer&) = delete;
            Renderer &operator=(const Renderer&) = delete;
        private:

    };
}
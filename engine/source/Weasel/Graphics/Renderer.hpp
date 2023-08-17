#pragma once

#include "Weasel/Graphics/RenderUtils.hpp"
#include "Weasel/Graphics/Cameras.hpp"
#include "Weasel/Graphics/Mesh.hpp"
#include "Weasel/Graphics/Material.hpp"

namespace Weasel {
    class Renderer {
        public:
            static std::unique_ptr<Renderer> Create();
            Renderer();
            ~Renderer();
            Renderer(const Renderer&) = delete;
            Renderer &operator=(const Renderer&) = delete;

            void BeginScene(std::shared_ptr<Camera> camera);
            void EndScene();
            void DrawMesh(const std::shared_ptr<Mesh> mesh);
        private:
            std::shared_ptr<Camera> m_Camera;

    };
}
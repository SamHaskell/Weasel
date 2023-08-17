#pragma once

#include "Weasel/Base/Base.hpp"
#include "Weasel/Core/Application.hpp"
#include "Weasel/Events/Events.hpp"
#include "Weasel/Graphics/Renderer.hpp"

namespace Weasel {
    class Layer {
        public:
            Layer(AppState state) {}
            virtual ~Layer() {}
            virtual void Update(f64 dt) {}
            virtual void LateUpdate(f64 dt) {}
            virtual void Render(const std::unique_ptr<Renderer>& renderer) {}
            virtual void RenderGUI() {}
            virtual bool OnEvent(Event& e) { return false; }
    };
}
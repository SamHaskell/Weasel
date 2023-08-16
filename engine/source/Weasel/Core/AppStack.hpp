#pragma once

#include "Weasel/Base/Base.hpp"
#include "Weasel/Core/Layer.hpp"

#include <algorithm>

namespace Weasel {
    class AppStack {
        public:
            AppStack() {}
            ~AppStack();
            void AddLayer(Layer* layer);
            void AddOverlay(Layer* overlay);
            void RemoveLayer(Layer* layer);
            void RemoveOverlay(Layer* overlay);
            std::vector<Layer*> Layers;
            std::vector<Layer*> Overlays;
        private:
    };
}
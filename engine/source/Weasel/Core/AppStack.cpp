#include "Weasel/Core/AppStack.hpp"
#include "Weasel/Core/Layer.hpp"

namespace Weasel {
    AppStack::~AppStack() {
        for (auto overlay : Overlays) { delete overlay; }
        for (auto layer : Layers) { delete layer; }
    }

    void AppStack::AddLayer(Layer* layer) {
        Layers.emplace_back(layer);
    }

    void AppStack::AddOverlay(Layer* overlay) {
        Overlays.emplace_back(overlay);
    }

    void AppStack::RemoveLayer(Layer* layer) {
        auto idx = std::find(Layers.begin(), Layers.end(), layer);
        Layers.erase(idx);
        delete layer;
    }

    void AppStack::RemoveOverlay(Layer* overlay) {
        auto idx = std::find(Overlays.begin(), Overlays.end(), overlay);
        Overlays.erase(idx);
        delete overlay;
    }
}
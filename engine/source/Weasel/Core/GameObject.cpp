#include "Weasel/Core/GameObject.hpp"

namespace Weasel {
    GameObject::GameObject() {
        for (u16 i = 0; i < MAX_COMPONENTS_PER_ENTITY; i++) {
            m_AvailableSlots.push(i);
            m_Components[i] = nullptr;
        }
    }

    GameObject::~GameObject() {

    }

    void GameObject::Update(f64 dt) {
        for (auto& c : m_Components) {
            c->Update(dt);
        }
    }

    void GameObject::OnEvent(Event& e) {
        switch (e.Tag) {
            case EventTag::WindowSizeEvent:
                // check to see if component implements a window size event
                break;
            default:
                break;
        }
        return;
    }
}
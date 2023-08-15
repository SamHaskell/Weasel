#include "Weasel/Core/GameObject.hpp"
#include "Weasel/Core/Scene.hpp"

namespace Weasel {
    GameObject::GameObject(Scene* scene) {
        CurrentScene = scene;
        for (u16 i = MAX_COMPONENTS_PER_ENTITY; i > 0; i--) {
            m_AvailableSlots.push(i - 1);
            m_Components[i - 1] = nullptr;
        }
    }

    GameObject::~GameObject() {

    }

    void GameObject::Awake() {
        for (auto& c : m_Components) {
            if (!c) { continue; }
            c->Awake();
        }
    }

    void GameObject::Update(f64 dt) {
        for (auto& c : m_Components) {
            if (!c) { continue; }
            c->Update(dt);
        }
    }

    void GameObject::LateUpdate(f64 dt) {
        for (auto& c : m_Components) {
            if (!c) { continue; }
            c->LateUpdate(dt);
        }
    }

    void GameObject::OnEvent(Event& e) {
        for (auto& c : m_Components) {
            if (!c) { continue; }
            switch (e.Tag) {
                case EventTag::WindowFramebufferSizeEvent:
                    c->OnWindowFramebufferResize(e.WindowFramebufferSizeEvent.Width, e.WindowFramebufferSizeEvent.Height);
                    break;
                default:
                    break;
            }
        }
    }
}
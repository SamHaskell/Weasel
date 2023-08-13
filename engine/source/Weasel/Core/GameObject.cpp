#include "Weasel/Core/GameObject.hpp"
#include "Weasel/Core/Scene.hpp"

namespace Weasel {
    glm::mat4 Transform::WorldTransform() {
        if (m_RequireUpdate) {
            m_WorldTransform = m_LocalTransform * m_Parent->WorldTransform();
        }
        return m_WorldTransform;
    }
    
    glm::vec3 Transform::WorldPosition() {
        return glm::vec3(WorldTransform()[3]);
    }

    glm::vec3 Transform::WorldForward() {

    }

    void Transform::SetLocalPosition(const glm::vec3& translation) {
        m_RequireUpdate = true;
    }


    void Transform::SetLocalRotation(const glm::vec3& forward, const glm::vec3& right) {
        m_RequireUpdate = true;
    }

    GameObject::GameObject(Scene* scene) {
        CurrentScene = scene;
        for (u16 i = MAX_COMPONENTS_PER_ENTITY; i > 0; i--) {
            m_AvailableSlots.push(i - 1);
            m_Components[i - 1] = nullptr;
        }
    }

    GameObject::~GameObject() {

    }

    void GameObject::Update(f64 dt) {
        for (auto& c : m_Components) {
            if (!c) { continue; }
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
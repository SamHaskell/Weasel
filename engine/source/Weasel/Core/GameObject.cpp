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
}
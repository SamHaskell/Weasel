#pragma once

#include "Weasel/Base/Base.hpp"
#include "Weasel/Core/Transform.hpp"
#include "Weasel/Events/Events.hpp"

#include <stack>

namespace Weasel {
    
    #define MAX_COMPONENTS_PER_ENTITY 64

    class GameObject;
    class Scene;

    class Component {
        public:
            Component(GameObject* owner) { m_Owner = owner; }
            virtual ~Component() {}
            virtual void Update(f64 dt) {}
        protected:
            GameObject* m_Owner;
    };

    class GameObject {
        public:
            GameObject(Scene* scene);
            ~GameObject();
            void Update(f64 dt);
            void OnEvent(Event& e);
            
            template <typename T>
            inline T* AddComponent() {
                auto i = m_AvailableSlots.top();
                T* out = new T(this);
                m_Components[i] = out;
                m_AvailableSlots.pop();
                return out;
            }

            template <typename T>
            inline void DestroyComponent(T *component) {
                for (u16 i = 0; i < MAX_COMPONENTS_PER_ENTITY; i++) {
                    if (m_Components[i] == component) {
                        m_Components[i]->~Component();
                        m_Components[i] = nullptr;
                        m_AvailableSlots.push(i);
                    }
                }
            }
            
            template <typename T>
            inline T* GetComponent() {
                for (auto c : m_Components) {
                    if (dynamic_cast<T*>(c) != nullptr) {
                        return (T*)c;
                    }
                }
                return nullptr;
            }

            template <typename T>
            inline bool TryGetComponent(T **outComponent) {
                for (auto c : m_Components) {
                    if (c == nullptr) {
                        continue;
                    }
                    if (dynamic_cast<T*>(c) != nullptr) {
                        *outComponent = (T*)c;
                        return true;
                    }
                }
                outComponent = nullptr;
                return false;
            }

            Transform Transform;
            Scene* CurrentScene;

        private:
            std::array<Component*, MAX_COMPONENTS_PER_ENTITY> m_Components; // Find out how expensive reallocating ~500 bytes is.
            std::stack<u16> m_AvailableSlots;
            u32 m_ID; // Make a GUID at some point?
    };
}
#pragma once

#include "Weasel/Base/Base.hpp"

#include <stack>

namespace Weasel {
    
    #define MAX_COMPONENTS_PER_ENTITY 64

    class GameObject;

    class Component {
        public:
            Component(GameObject* owner) { m_Owner = owner; }
            virtual ~Component() { }
        protected:
            GameObject* m_Owner;
    };

    class SomeData : public Component {
        public:
            SomeData(GameObject* owner) : Component(owner) {}
            ~SomeData() { LOG_DEBUG("SomeData destroyed!"); }
            inline int GetFive() { return 5; }
        private:
    };

    class SomeOtherData : public Component {
        public:
            SomeOtherData(GameObject* owner) : Component(owner) {}
            ~SomeOtherData() { LOG_DEBUG("SomeOtherData destroyed!"); }
            inline int GetSix() { return 6; }
        private:
    };

    class Transform {
        public:
            Transform() {}
            ~Transform() {}
        private:
            std::shared_ptr<Transform> m_Parent;
            std::vector<std::shared_ptr<Transform>> m_Children;
            glm::mat4 m_LocalTransform;
            glm::mat4 m_WorldTransform;
            bool m_RequireUpdate;
    };

    class GameObject {
        public:
            GameObject();
            ~GameObject();
            
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

        private:
            std::array<Component*, MAX_COMPONENTS_PER_ENTITY> m_Components; // Find out how expensive reallocating ~500 bytes is.
            std::stack<u16> m_AvailableSlots;
            u32 m_ID; // Make a GUID at some point?
    };
}
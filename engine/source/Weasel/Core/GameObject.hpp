#pragma once

#include "Weasel/Base/Base.hpp"

namespace Weasel {
    class Transform {
        public:
            Transform();
            ~Transform();
        private:
            Transform* m_Parent;
            glm::mat4 m_LocalTransform;
            glm::mat4 m_WorldTransform;
            bool m_RequireUpdate;
    };

    class GameObject {
        public:
            GameObject();
            ~GameObject();
            Transform Transform;
        private:
            u32 m_ID; // Make a GUID at some point
    };
}
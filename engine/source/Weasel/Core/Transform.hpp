#pragma once

#include "Weasel/Base/Base.hpp"

namespace Weasel {
    class Transform {
        public:
            Transform() : m_Valid(false) {}
            ~Transform() {}
            void Invalidate();

            glm::mat4 WorldTransform();
            glm::quat WorldRotation();
            glm::vec3 WorldPosition();

            glm::mat4 LocalTransform();
            glm::quat LocalRotation();
            glm::vec3 LocalPosition();
            glm::vec3 LocalScale();

            glm::vec3 Forward();
            glm::vec3 Up();
            glm::vec3 Right();

            void SetLocalRotation(const glm::quat& rotation);
            void SetLocalPosition(const glm::vec3& position);
            void SetLocalScale(const glm::vec3& scale);            

            void Translate(const glm::vec3& displacement);
            void Rotate(const glm::vec3& axis, f32 angle);
        private:
            bool m_Valid;
            std::shared_ptr<Transform> m_Parent;
            std::vector<std::shared_ptr<Transform>> m_Children;
            glm::quat m_LocalRotation = glm::quat(1.0, 0.0, 0.0, 0.0);
            glm::vec3 m_LocalPosition = glm::vec3(0.0, 0.0, 0.0);
            glm::vec3 m_LocalScale = glm::vec3(1.0, 1.0, 1.0);
            glm::mat4 m_LocalTransform;
            glm::mat4 m_WorldTransform;
    };
}
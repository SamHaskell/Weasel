#pragma once

#include "Weasel/Graphics/RenderUtils.hpp"

namespace Weasel {
    class Camera {
        public:
            inline glm::vec3 Position() { return m_Position; }
            inline glm::vec3 Forward() { return m_Forward; }
            inline glm::vec3 Up() { return m_Up; }
            glm::mat4 ViewMatrix();
            glm::mat4 ProjectionMatrix();
            glm::mat4 ViewProjectionMatrix();

            void SetPosition(const glm::vec3& position);
            void SetForward(const glm::vec3& forward);
            void SetPerspectiveProjection(f32 fovy, f32 aspect, f32 near, f32 far);
            void SetOrthographicProjection(f32 left, f32 right, f32 bottom, f32 top, f32 near, f32 far);
            void SetViewDirection(glm::vec3 position, glm::vec3 forward, glm::vec3 up);
            void SetViewTarget(glm::vec3 position, glm::vec3 target, glm::vec3 up);
        private:
            bool m_Dirty;
            glm::mat4 m_ProjectionMatrix {1.0f};
            glm::mat4 m_ViewMatrix {1.0f};
            glm::vec3 m_Position;
            glm::vec3 m_Forward;
            glm::vec3 m_Up;
        
    };
}
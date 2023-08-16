#include "Weasel/Graphics/Cameras.hpp"

namespace Weasel {
    glm::mat4 Camera::ViewMatrix() {
        return m_ViewMatrix;
    }

    glm::mat4 Camera::ProjectionMatrix() {
        return m_ProjectionMatrix;
    }

    glm::mat4 Camera::ViewProjectionMatrix() {
        return m_ProjectionMatrix * m_ViewMatrix;
    }

    void Camera::SetPosition(const glm::vec3& position) {
        m_Position = position;
        m_ViewMatrix = glm::lookAt(position, position + m_Forward, m_Up);
    }

    void Camera::SetForward(const glm::vec3& forward) {
        m_Forward = glm::normalize(forward);
        m_ViewMatrix = glm::lookAt(m_Position, m_Position + forward, m_Up);
    }

    void Camera::SetPerspectiveProjection(f32 fovy, f32 aspect, f32 near, f32 far) {
        m_ProjectionMatrix = glm::perspective(glm::radians(fovy), aspect, near, far);
    }

    void Camera::SetOrthographicProjection(f32 left, f32 right, f32 bottom, f32 top, f32 near, f32 far) {
        m_ProjectionMatrix = glm::ortho(left, right, bottom, top, near, far);
    }

    void Camera::SetViewDirection(glm::vec3 position, glm::vec3 forward, glm::vec3 up) {
        m_Position = position;
        m_Forward = glm::normalize(forward);
        m_Up = up;
        m_ViewMatrix = glm::lookAt(position, position + forward, up);
    }

    void Camera::SetViewTarget(glm::vec3 position, glm::vec3 target, glm::vec3 up) {
        m_Position = position;
        m_Forward = glm::normalize(target - position);
        m_Up = up;
        m_ViewMatrix = glm::lookAt(position, target, up);
    }
}
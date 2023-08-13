#include "Weasel/Graphics/Cameras.hpp"

namespace Weasel {
    void Camera::SetPerspectiveProjection(f32 fovy, f32 aspect, f32 near, f32 far) {
        ProjectionMatrix = glm::perspective(glm::radians(fovy), aspect, near, far);
    }

    void Camera::SetOrthographicProjection(f32 left, f32 right, f32 bottom, f32 top, f32 near, f32 far) {
        ProjectionMatrix = glm::ortho(left, right, bottom, top, near, far);
    }

    void Camera::SetViewDirection(glm::vec3 position, glm::vec3 forward, glm::vec3 up) {
        Position = position;
        Forward = glm::normalize(forward);
        ViewMatrix = glm::lookAt(position, position + forward, up);
    }

    void Camera::SetViewTarget(glm::vec3 position, glm::vec3 target, glm::vec3 up) {
        Position = position;
        Forward = glm::normalize(target - position);
        ViewMatrix = glm::lookAt(position, target, up);
    }
}
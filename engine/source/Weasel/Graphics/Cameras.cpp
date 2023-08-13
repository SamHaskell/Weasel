#include "Weasel/Graphics/Cameras.hpp"

namespace Weasel {
    std::shared_ptr<Camera> Camera::CreatePerspective(f32 fovy, f32 aspect, f32 near, f32 far) {
        auto cam = std::make_shared<Camera>();
        cam->SetPerspectiveProjection(fovy, aspect, near, far);
        return cam;
    }

    std::shared_ptr<Camera> Camera::CreateOrthographic(f32 left, f32 right, f32 bottom, f32 top, f32 near, f32 far) {
        auto cam = std::make_shared<Camera>();
        cam->SetOrthographicProjection(left, right, bottom, top, near, far);
    }

    void Camera::SetPerspectiveProjection(f32 fovy, f32 aspect, f32 near, f32 far) {
        ProjectionMatrix = glm::perspective(glm::radians(fovy), aspect, near, far);
    }

    void Camera::SetOrthographicProjection(f32 left, f32 right, f32 bottom, f32 top, f32 near, f32 far) {
        ProjectionMatrix = glm::ortho(left, right, bottom, top, near, far);
    }

    void Camera::SetViewDirection(glm::vec3 position, glm::vec3 forward, glm::vec3 up) {
        ViewMatrix = glm::lookAt(position, position + forward, up);
    }

    void Camera::SetViewTarget(glm::vec3 position, glm::vec3 target, glm::vec3 up) {
        ViewMatrix = glm::lookAt(position, target, up);
    }
}
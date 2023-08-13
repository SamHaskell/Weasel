#pragma once

#include "Weasel/Graphics/RenderUtils.hpp"

namespace Weasel {
    struct Camera {
        static std::shared_ptr<Camera> CreatePerspective(f32 fovy, f32 aspect, f32 near, f32 far);
        static std::shared_ptr<Camera> CreateOrthographic(f32 left, f32 right, f32 bottom, f32 top, f32 near, f32 far);
        glm::mat4 ProjectionMatrix {1.0f};
        glm::mat4 ViewMatrix {1.0f};
        void SetPerspectiveProjection(f32 fovy, f32 aspect, f32 near, f32 far);
        void SetOrthographicProjection(f32 left, f32 right, f32 bottom, f32 top, f32 near, f32 far);
        void SetViewDirection(glm::vec3 position, glm::vec3 forward, glm::vec3 up);
        void SetViewTarget(glm::vec3 position, glm::vec3 target, glm::vec3 up);
    };
}
#pragma once

#include "Weasel/Graphics/RenderUtils.hpp"

namespace Weasel {
    struct DirectionalLight {
        glm::vec3 Direction;
        glm::vec3 Ambient;
        glm::vec3 Diffuse;
        glm::vec3 Specular;
    };

    struct PointLight {
        glm::vec3 Position;
        glm::vec3 Ambient;
        glm::vec3 Diffuse;
        glm::vec3 Specular;
        f32 Constant;
        f32 Linear;
        f32 Quadratic;
    };
}
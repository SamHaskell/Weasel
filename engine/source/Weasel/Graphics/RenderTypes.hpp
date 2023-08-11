#pragma once

#include "Weasel/Base/Base.hpp"

#include "glad/glad.h"

#include <vector>
#include <array>
#include <unordered_map>

using Index = u32;

struct Vertex {
    glm::vec3 Position = {0.0f, 0.0f, 0.0f};
    glm::vec3 Normal = {0.0f, 0.0f, 0.0f};
    glm::vec3 Color = {1.0f, 1.0f, 1.0f};
    glm::vec2 TexCoord = {0.0f, 0.0f};
};
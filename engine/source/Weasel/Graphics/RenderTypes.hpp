#pragma once

#include "Weasel/Base/Base.hpp"

#include "glad/glad.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/quaternion.hpp"

#include <vector>
#include <array>
#include <unordered_map>

using Index = u32;

struct Vertex {
    glm::vec3 Position;
    glm::vec3 Normal;
    glm::vec3 Albedo;
    glm::vec2 TexCoord;
};
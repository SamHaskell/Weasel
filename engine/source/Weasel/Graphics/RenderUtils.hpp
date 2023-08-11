#pragma once

#include "Weasel/Graphics/RenderTypes.hpp"

#include <fstream>
#include <sstream>

namespace Weasel {
    std::string load_shader_source(const std::string& path);
}
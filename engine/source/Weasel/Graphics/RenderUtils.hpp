#pragma once

#include "Weasel/Graphics/RenderTypes.hpp"

#include "assimp/Importer.hpp"
#include "assimp/scene.h"
#include "assimp/postprocess.h"

#include <fstream>
#include <sstream>

namespace Weasel {
    std::string load_shader_source(const std::string& path);
}
#include "Weasel/Graphics/RenderUtils.hpp"

namespace Weasel {
    std::string load_shader_source(const std::string& path) {
        std::string code;
        std::ifstream file(path);
        if (!file.is_open()) {
            LOG_ERROR("Failed to open shader source: %s", path.c_str());
            ASSERT(false, "Failure to read shader.");
        }
        std::stringstream stream;
        stream << file.rdbuf();
        file.close();
        code = stream.str();
        return code;
    }
}
#pragma once

#include "Weasel/Graphics/RenderUtils.hpp"

namespace Weasel {
    class Material {
        public:
            static std::shared_ptr<Material> Create();
            Material();
            ~Material();
            Material(const Material&) = delete;
            Material &operator=(const Material&) = delete;
        private:

    };    
}
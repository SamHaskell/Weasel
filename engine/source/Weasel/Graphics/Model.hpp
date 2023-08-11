#pragma once

#include "Weasel/Graphics/RenderUtils.hpp"

namespace Weasel {
    class Model {
        public:
            static std::shared_ptr<Model> Create();
            Model();
            ~Model();
            Model(const Model&) = delete;
            Model &operator=(const Model&) = delete;
        private:

    };
}
#include "Weasel/Graphics/Material.hpp"

namespace Weasel {
    std::shared_ptr<Material> Material::Create() {
        return std::make_shared<Material>();
    }

    Material::Material() {

    }

    Material::~Material() {

    }
}
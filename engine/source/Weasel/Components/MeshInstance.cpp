#include "Weasel/Components/MeshInstance.hpp"

namespace Weasel {
    MeshInstance::MeshInstance(GameObject* owner) : Component(owner) {

    }

    MeshInstance::MeshInstance(GameObject* owner, std::shared_ptr<Mesh> mesh, std::shared_ptr<Material> material) : Component(owner) {
        m_Mesh = mesh;
        m_Material = material;
    }

    MeshInstance::~MeshInstance() {

    }
}
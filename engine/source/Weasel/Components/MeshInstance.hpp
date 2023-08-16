#pragma once

#include "Weasel/Core/GameObject.hpp"
#include "Weasel/Base/Base.hpp"

#include "Weasel/Graphics/Mesh.hpp"
#include "Weasel/Graphics/Material.hpp"

namespace Weasel {
    class MeshInstance : public Component {
        public:
            MeshInstance(GameObject* owner);
            ~MeshInstance();
            inline void SetMesh(std::shared_ptr<Mesh> mesh) { m_Mesh = mesh; }
            inline void SetMaterial(std::shared_ptr<Material> material) { m_Material = material; }
            inline std::shared_ptr<Material> GetMaterial() { return m_Material; }
            inline std::shared_ptr<Mesh> GetMesh() { return m_Mesh; }
        private:
            std::shared_ptr<Mesh> m_Mesh;
            std::shared_ptr<Material> m_Material;
    };
}
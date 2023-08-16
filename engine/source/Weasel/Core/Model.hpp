#pragma once

#include "Weasel/Base/Base.hpp"
#include "Weasel/Graphics/Mesh.hpp"
#include "Weasel/Graphics/Material.hpp"

namespace Weasel {
    class Model {
        public:
            static std::shared_ptr<Model> Load(const std::string& path);
            Model(const std::string& path);
            ~Model();
            std::vector<std::shared_ptr<Mesh>> m_Meshes;
        private:
            u32 m_VertexCount = 0;
            u32 m_IndexCount = 0;
            std::string m_RootDirectory;

            void ProcessNode(aiNode* node, const aiScene* scene);
            std::shared_ptr<Mesh> ProcessMesh(aiMesh* mesh, const aiScene* scene);
    };
}
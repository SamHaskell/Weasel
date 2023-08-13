#include "Weasel/Core/Model.hpp"

namespace Weasel {
    std::shared_ptr<Model> Model::Load(const std::string& path) {
        return std::make_shared<Model>(path);
    }
    
    Model::Model(const std::string& path) {
        Assimp::Importer import;
        const aiScene* scene = import.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);
        bool ok = (scene && !(scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE) && scene->mRootNode);
        if (!ok)
            LOG_ERROR("Failure loading model from file: %s. Error: %s", path.c_str(), import.GetErrorString());
        ASSERT(ok, "Assimp failed to load model from file.");
        m_RootDirectory = path.substr(0, path.find_last_of('/'));
        ProcessNode(scene->mRootNode, scene);

        LOG_DEBUG("Model loaded from: %s. Vertices: %u, Indices: %u", m_RootDirectory.c_str(), m_VertexCount, m_IndexCount);
    }
    
    Model::~Model() {

    }

    void Model::ProcessNode(aiNode* node, const aiScene* scene) {
        for (u32 i = 0; i < node->mNumMeshes; i++) {
            aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
            m_Meshes.push_back(ProcessMesh(mesh, scene));
        }

        for (u32 i = 0; i < node->mNumChildren; i++) {
            ProcessNode(node->mChildren[i], scene);
        }
    }

    std::shared_ptr<Mesh> Model::ProcessMesh(aiMesh* mesh, const aiScene* scene) {
        std::vector<Vertex> vertices;
        std::vector<u32> indices;
        
        for (u32 i = 0; i < mesh->mNumVertices; i++) {
            Vertex vert;

            vert.Position.x = mesh->mVertices[i].x;
            vert.Position.y = mesh->mVertices[i].y;
            vert.Position.z = mesh->mVertices[i].z;
            
            vert.Normal.x = mesh->mNormals[i].x;
            vert.Normal.y = mesh->mNormals[i].y;
            vert.Normal.z = mesh->mNormals[i].z;

            if (mesh->mTextureCoords[0]) {
                vert.TexCoord.x = mesh->mTextureCoords[0][i].x;
                vert.TexCoord.y = mesh->mTextureCoords[0][i].y;
            } else {
                vert.TexCoord = glm::vec2(0.0f, 0.0f);
            }

            vertices.push_back(vert);
        }

        for (u32 i = 0; i < mesh->mNumFaces; i++) {
            aiFace face = mesh->mFaces[i];
            for (u32 j = 0; j < face.mNumIndices; j++) {
                indices.push_back(face.mIndices[j]);
            }
        }

        if (mesh->mMaterialIndex >= 0) {
            // TODO: Process materials.
        }

        m_VertexCount += static_cast<u32>(vertices.size());
        m_IndexCount += static_cast<u32>(indices.size());

        return Mesh::Create(vertices, indices);
    }
}
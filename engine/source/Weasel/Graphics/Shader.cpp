#include "Weasel/Graphics/Shader.hpp"

namespace Weasel {
    std::shared_ptr<Shader> Shader::Create(const std::string& vertPath, const std::string& fragPath) {
        return std::make_shared<Shader>(vertPath, fragPath);
    }

    Shader::Shader(const std::string& vertPath, const std::string& fragPath) {

    }

    Shader::~Shader() {

    }

    std::shared_ptr<ShaderRepository> ShaderRepository::Create() {
        return std::make_shared<ShaderRepository>();
    }

    ShaderRepository::ShaderRepository() {
        // Potentially attempt to load all shaders from some special directories upon construction
    }

    void ShaderRepository::Add(const std::string& name, const std::shared_ptr<Shader> shader) {
        ASSERT(m_ShaderLookup.find(name) != m_ShaderLookup.end(), "A Shader with the same name already exists.");
        m_ShaderLookup[name] = shader;
    }

    std::shared_ptr<Shader> ShaderRepository::Load(const std::string& name, const std::string& vertPath, const std::string& fragPath) {
        auto shader = Shader::Create(vertPath, fragPath);
        ASSERT(m_ShaderLookup.find(name) == m_ShaderLookup.end(), "A Shader with the same name already exists.");
        m_ShaderLookup[name] = shader;
        return shader;
    }

    std::shared_ptr<Shader> ShaderRepository::Get(const std::string& name) {
        ASSERT(m_ShaderLookup.find(name) != m_ShaderLookup.end(), "Failed shader lookup: Shader does not exist.")
        return m_ShaderLookup[name];    
    }
}
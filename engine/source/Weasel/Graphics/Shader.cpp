#include "Weasel/Graphics/Shader.hpp"

namespace Weasel {
    std::shared_ptr<Shader> Shader::Create(const std::string& vertPath, const std::string& fragPath) {
        return std::make_shared<Shader>(vertPath, fragPath);
    }

    Shader::Shader(const std::string& vertPath, const std::string& fragPath) {
        u32 vertShader, fragShader;
        i32 success;

        std::string vertCode = load_shader_source(vertPath);
        const char* vertCodeStr = vertCode.c_str();
        vertShader = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertShader, 1, &vertCodeStr, NULL);
        glCompileShader(vertShader);
        glGetShaderiv(vertShader, GL_COMPILE_STATUS, &success);
        if (success == GL_FALSE) {
            char infoLog[512];
            glGetShaderInfoLog(vertShader, 512, NULL, infoLog);
            LOG_ERROR("Shader Compilation Error: %s", infoLog);
        }

        std::string fragCode = load_shader_source(fragPath);
        const char* fragCodeStr = fragCode.c_str();
        fragShader = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragShader, 1, &fragCodeStr, NULL);
        glCompileShader(fragShader);
        glGetShaderiv(fragShader, GL_COMPILE_STATUS, &success);
        if (success == GL_FALSE) {
            char infoLog[512];
            glGetShaderInfoLog(fragShader, 512, NULL, infoLog);
            LOG_ERROR("Shader Compilation Error: %s", infoLog);
        }

        m_ShaderID = glCreateProgram();
        glAttachShader(m_ShaderID, vertShader);
        glAttachShader(m_ShaderID, fragShader);
        glLinkProgram(m_ShaderID);
        glGetProgramiv(m_ShaderID, GL_LINK_STATUS, &success);
        if(!success)
        {
            char infoLog[512];
            glGetProgramInfoLog(m_ShaderID, 512, NULL, infoLog);
            LOG_ERROR("Shader Linking Error: %s", infoLog);
        }

        glDeleteShader(vertShader);
        glDeleteShader(fragShader);
    }

    Shader::~Shader() {

    }

    void Shader::SetUniformFloat(const char* name, const f32& value) {
        glUniform1f(glGetUniformLocation(m_ShaderID, name), value);
    }

    void Shader::SetUniformVec3(const char* name, const glm::vec3& vector) {
        glUniform3fv(glGetUniformLocation(m_ShaderID, name), 1, &vector[0]);
    }
    
    void Shader::SetUniformMat4(const char* name, const glm::mat4& matrix) {
        glUniformMatrix4fv(glGetUniformLocation(m_ShaderID, name), 1, GL_FALSE, &matrix[0][0]);
    }

    void Shader::SetSamplerSlot(const char* name, const u32 slot) {
        glUniform1i(glGetUniformLocation(m_ShaderID, name), slot);
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
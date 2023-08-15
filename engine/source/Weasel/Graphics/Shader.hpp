#pragma once

#include "Weasel/Graphics/RenderUtils.hpp"

namespace Weasel {
    class Shader {
        public:
            static std::shared_ptr<Shader> Create(const std::string& vertPath, const std::string& fragPath);
            Shader(const std::string& vertPath, const std::string& fragPath);
            ~Shader();
            Shader(const Shader&) = delete;
            Shader &operator=(const Shader&) = delete;
            inline void Bind() { glUseProgram(m_ShaderID); }

            void SetUniformFloat(const char* name, const f32& value);
            void SetUniformVec3(const char* name, const glm::vec3& vector);
            void SetUniformMat4(const char* name, const glm::mat4& matrix);
            void SetSamplerSlot(const char* name, const u32 slot);
        private:
            u32 m_ShaderID;
    };

    class ShaderRepository {
        public:
            static std::shared_ptr<ShaderRepository> Create();
            ShaderRepository();
            void Add(const std::string& name, const std::shared_ptr<Shader> shader);
            std::shared_ptr<Shader> Load(const std::string& name, const std::string& vertPath, const std::string& fragPath);
            std::shared_ptr<Shader> Get(const std::string& name);
        private:
            std::unordered_map<std::string, std::shared_ptr<Shader>> m_ShaderLookup;
    };
}
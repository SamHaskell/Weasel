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
            inline void Bind() { glUseProgram(m_ShaderProgram); }
        private:
            void Compile();
            u32 m_ShaderProgram;
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
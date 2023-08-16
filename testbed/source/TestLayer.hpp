#pragma once

#include "Weasel.hpp"

class TestLayer : public Weasel::Layer {
    public:
        TestLayer();
        ~TestLayer();
        virtual void Update(f64 dt) override;
        virtual void LateUpdate(f64 dt) override;
        virtual void ImGuiRender() override;
        virtual void Render(const std::unique_ptr<Weasel::Renderer>& renderer) override;
        virtual bool OnEvent(Weasel::Event& e) override;
    private:
        std::shared_ptr<Weasel::ShaderRepository> m_ShaderRepository;
        std::unique_ptr<Weasel::Scene> m_ActiveScene;
        Weasel::PointLight m_PointLights[4];
        Weasel::DirectionalLight m_DirectionalLight;
        std::shared_ptr<Weasel::Model> m_BackpackModel;
        std::shared_ptr<Weasel::GameObject> m_Cube;
        std::shared_ptr<Weasel::Texture2D> m_Diffuse;
        std::shared_ptr<Weasel::Texture2D> m_Normal;
        std::shared_ptr<Weasel::Texture2D> m_Specular;
        
};
#pragma once

#include "Weasel.hpp"

class EditorLayer : public Weasel::Layer {
    public:
        EditorLayer();
        ~EditorLayer();
        virtual void Update(f64 dt) override;
        virtual void LateUpdate(f64 dt) override;
        virtual void ImGuiRender() override;
        virtual void Render(const std::unique_ptr<Weasel::Renderer>& renderer) override;
        virtual bool OnEvent(Weasel::Event& e) override;
    private:
        glm::vec4 m_TestColor;
};
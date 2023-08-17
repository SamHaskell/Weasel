#pragma once

#include "Weasel.hpp"

namespace Weasel {
    class EditorLayer : public Layer {
        public:
            EditorLayer(AppState state);
            ~EditorLayer();
            virtual void Update(f64 dt) override;
            virtual void LateUpdate(f64 dt) override;
            virtual void Render(const std::unique_ptr<Renderer>& renderer) override;
            virtual void RenderGUI() override;
            virtual bool OnEvent(Event& e) override;
        private:
            Rect2D m_Viewport;
            Rect2D m_ScreenExtents;
            std::shared_ptr<Framebuffer> m_Framebuffer;
            FramebufferSpecification m_FramebufferSpec;
            bool m_FramebufferInvalid;
            std::shared_ptr<ShaderRepository> m_ShaderRepository;
            std::unique_ptr<Scene> m_ActiveScene;
            PointLight m_PointLights[4];
            DirectionalLight m_DirectionalLight;
            std::shared_ptr<Model> m_BackpackModel;
            std::shared_ptr<GameObject> m_Backpack;
            std::shared_ptr<Texture2D> m_Diffuse;
            std::shared_ptr<Texture2D> m_Normal;
            std::shared_ptr<Texture2D> m_Specular;
    };
}
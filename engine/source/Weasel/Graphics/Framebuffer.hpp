#pragma once

#include "Weasel/Graphics/RenderUtils.hpp"
#include "Weasel/Graphics/Textures.hpp"

namespace Weasel {
    struct FramebufferSpecification {
        u32 Width;
        u32 Height;
        u32 SampleCount = 1;
        GLenum Format;
    };

    class Framebuffer {
        public:
            static std::shared_ptr<Framebuffer> Create(const FramebufferSpecification& spec);
            Framebuffer(const FramebufferSpecification& spec);
            ~Framebuffer();
            std::shared_ptr<Framebuffer> Duplicate();
            void Recreate(const FramebufferSpecification& spec);
            inline FramebufferSpecification GetSpecification() { return m_Spec; }
            inline void Bind() { 
                glBindFramebuffer(GL_FRAMEBUFFER, m_FramebufferID);
            }
            static void Unbind() { 
                glBindFramebuffer(GL_FRAMEBUFFER, 0);
            }
            inline u32 GetColorAttachmentID() { return m_ColorAttachment->GetTextureID(); }
            inline u32 GetDepthAttachmentID() { return m_DepthAttachment->GetTextureID(); }
        private:
            u32 m_FramebufferID;
            FramebufferSpecification m_Spec;
            std::shared_ptr<Texture2D> m_ColorAttachment;
            std::shared_ptr<Texture2D> m_DepthAttachment;
    };
}
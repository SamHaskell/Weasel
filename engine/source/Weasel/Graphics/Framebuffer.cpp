#include "Weasel/Graphics/Framebuffer.hpp"

namespace Weasel {
    std::shared_ptr<Framebuffer> Framebuffer::Create(const FramebufferSpecification& spec) {
        return std::make_shared<Framebuffer>(spec);
    }
    Framebuffer::Framebuffer(const FramebufferSpecification& spec) {
        m_Spec = spec;
        
        glGenFramebuffers(1, &m_FramebufferID);
        glBindFramebuffer(GL_FRAMEBUFFER, m_FramebufferID);

        TextureSpecification2D colorAttachmentSpec = {
            .Width = spec.Width,
            .Height = spec.Height,
            .ImageFormat = GL_RGB,
            .Format = GL_RGB
        };

        m_ColorAttachment = Texture2D::Create(colorAttachmentSpec);

        glFramebufferTexture2D(
            GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, 
            GL_TEXTURE_2D, m_ColorAttachment->GetTextureID(),
            0
        );

        TextureSpecification2D depthStencilAttachmentSpec = {
            .Width = spec.Width,
            .Height = spec.Height,
            .ImageFormat = GL_DEPTH24_STENCIL8,
            .Format = GL_DEPTH_STENCIL,
            .DataType = GL_UNSIGNED_INT_24_8
        };

        m_DepthAttachment = Texture2D::Create(depthStencilAttachmentSpec);

        glFramebufferTexture2D(
            GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT,
            GL_TEXTURE_2D, m_DepthAttachment->GetTextureID(),
            0
        );

        bool complete = (glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE);
        ASSERT(complete, "Framebuffer is incomplete.");

        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }

    Framebuffer::~Framebuffer() {
        glDeleteFramebuffers(1, &m_FramebufferID);
    }

    std::shared_ptr<Framebuffer> Framebuffer::Duplicate() {
        return Framebuffer::Create(m_Spec);
    }
}
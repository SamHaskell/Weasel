#pragma once

#include "stb_image.h"

#include "Weasel/Graphics/RenderUtils.hpp"

namespace Weasel {
    struct TextureSpecification2D {
        GLenum Format; // Format of pizel data, i.e. GL_RGB / GL_DEPTH_STENCIL
        GLenum ImageFormat; // Internal format, can be specified as a sized format i.e. GL_RGBA8_SNORM
        u32 Width;
        u32 Height;
        GLenum DataType = GL_UNSIGNED_BYTE;
    };

    class Texture2D {
        public:
            static std::shared_ptr<Texture2D> Create(const std::string& path);
            static std::shared_ptr<Texture2D> Create(const TextureSpecification2D& spec);
            Texture2D(const std::string& path);
            Texture2D(const TextureSpecification2D& spec);
            ~Texture2D();

            inline u32 GetTextureID() { return m_TextureID; }

            void Bind(u32 slot);
            static void Unbind();

        private:
            u32 m_TextureID;
            TextureSpecification2D m_Spec;
    };
}
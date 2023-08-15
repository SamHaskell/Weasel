#pragma once

#include "stb_image.h"

#include "Weasel/Graphics/RenderUtils.hpp"

namespace Weasel {
    class Texture2D {
        public:
            static std::shared_ptr<Texture2D> Create(const std::string& path);
            Texture2D(const std::string& path);
            ~Texture2D();

            void Bind(u32 slot);
            static void Unbind();

        private:
            u32 m_TextureID;
            GLenum m_Format;
            GLenum m_ImageFormat;
            i32 m_Width;
            i32 m_Height;
            i32 m_NumChannels;
    };
}
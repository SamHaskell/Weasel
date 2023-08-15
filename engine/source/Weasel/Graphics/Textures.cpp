#include "Weasel/Graphics/Textures.hpp"

namespace Weasel {
    std::shared_ptr<Texture2D> Texture2D::Create(const std::string& path) {
        return std::make_shared<Texture2D>(path);
    }

    Texture2D::Texture2D(const std::string& path) {
        stbi_set_flip_vertically_on_load(true);
        u8* data = stbi_load(path.c_str(), &m_Width, &m_Height, &m_NumChannels, 0);
        ASSERT(data, "STBI Failed to load texture.");
        m_Format = (m_NumChannels == 3) ? GL_RGB : GL_RGBA;
        m_ImageFormat = (m_NumChannels == 3) ? GL_RGB8 : GL_RGBA8;

        glGenTextures(1, &m_TextureID);
        glBindTexture(GL_TEXTURE_2D, m_TextureID);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(m_TextureID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(m_TextureID, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexImage2D(GL_TEXTURE_2D, 0, m_ImageFormat, m_Width, m_Height, 0, m_Format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, 0);

        stbi_image_free(data);
    }

    Texture2D::~Texture2D() {
        glDeleteTextures(1, &m_TextureID);
    }

    void Texture2D::Bind(u32 slot) {
        glActiveTexture(GL_TEXTURE0 + slot);
        glBindTexture(GL_TEXTURE_2D, m_TextureID);
    }

    void Texture2D::Unbind() {
        glBindTexture(GL_TEXTURE_2D, 0);
    }
}
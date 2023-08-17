#include "Weasel/Graphics/Textures.hpp"

namespace Weasel {
    std::shared_ptr<Texture2D> Texture2D::Create(const TextureSpecification2D& spec) {
        return std::make_shared<Texture2D>(spec); }

    std::shared_ptr<Texture2D> Texture2D::Create(const std::string& path) {
        return std::make_shared<Texture2D>(path); }

    Texture2D::Texture2D(const std::string& path) {
        stbi_set_flip_vertically_on_load(true);
        i32 width, height, numChannels;
        u8* data = stbi_load(path.c_str(), &width, &height, &numChannels, 0);
        ASSERT(data, "STBI Failed to load texture.");
        m_Spec.Width = (u32)width;
        m_Spec.Height = (u32)height;
        m_Spec.Format = (numChannels == 3) ? GL_RGB : GL_RGBA;
        m_Spec.ImageFormat = (numChannels == 3) ? GL_RGB8 : GL_RGBA8;

        glGenTextures(1, &m_TextureID);
        glBindTexture(GL_TEXTURE_2D, m_TextureID);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(m_TextureID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(m_TextureID, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexImage2D(GL_TEXTURE_2D, 0, m_Spec.ImageFormat, m_Spec.Width, m_Spec.Height, 0, m_Spec.Format, m_Spec.DataType, data);
        glGenerateMipmap(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, 0);

        stbi_image_free(data);
    }

    Texture2D::Texture2D(const TextureSpecification2D& spec) {
        m_Spec = spec;
        glGenTextures(1, &m_TextureID);
        glBindTexture(GL_TEXTURE_2D, m_TextureID);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); 
        glTexImage2D(GL_TEXTURE_2D, 0, spec.ImageFormat, spec.Width, spec.Height, 0, spec.Format, m_Spec.DataType, NULL);
        glBindTexture(GL_TEXTURE_2D, 0);
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
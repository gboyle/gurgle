
#include "texture.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>

//////////////////////////////////////////////////////////////////////////

Texture::Texture(std::string const &filepath)
    : m_renderer_id(0),
      m_filepath(filepath),
      m_width(0),
      m_height(0),
      m_bpp(0),
      m_local_buffer(nullptr)
{
    // OpenGL expects origin at the bottom left
    stbi_set_flip_vertically_on_load(1);

    m_local_buffer = stbi_load(m_filepath.c_str(), &m_width, &m_height, &m_bpp, 4);

    GLCall(glGenTextures(1, &m_renderer_id));

    bind();

    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE)); // horizontal
    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE)); // vertical

    GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_width, m_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_local_buffer));

    unbind();

    if (m_local_buffer)
    {
        // could keep around if needed but for now, delete right away
        stbi_image_free(m_local_buffer);
        m_renderer_id = 0;
    }
}

Texture::~Texture()
{
    GLCall(glDeleteTextures(1, &m_renderer_id));
}

//////////////////////////////////////////////////////////////////////////

void Texture::bind(unsigned int slot) const
{
    GLCall(glActiveTexture(GL_TEXTURE0 + slot));
    GLCall(glBindTexture(GL_TEXTURE_2D, m_renderer_id));
}

void Texture::unbind() const
{
    GLCall(glBindTexture(GL_TEXTURE_2D, 0));
}

//////////////////////////////////////////////////////////////////////////
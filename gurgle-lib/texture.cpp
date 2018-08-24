
#include "texture.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>

//////////////////////////////////////////////////////////////////////////

Texture::Texture()
    : m_renderer_id(0),
      m_width(0),
      m_height(0),
      m_bpp(0),
      m_local_buffer(nullptr)
{
}

void Texture::open(std::string const &filepath)
{
    m_filepath = filepath;

    // OpenGL expects origin at the bottom left
    stbi_set_flip_vertically_on_load(1);

    m_local_buffer = stbi_load(m_filepath.c_str(), &m_width, &m_height, &m_bpp, 4);

    // unsigned char *p = m_local_buffer;
    // unsigned char *pend = m_local_buffer + 4 * m_width * m_height;

    // while (p < pend)
    // {
    //     *p++ = 250;
    //     *p++ = 150;
    //     *p++ = 50;
    //     *p++ = 255;
    // }

    GLCall(glGenTextures(1, &m_renderer_id));

    bind();

    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE)); // horizontal
    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE)); // vertical

    // float color[] = {1.0f, 0.0f, 0.0f, 1.0f};
    // GLCall(glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, color));

    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));

    // GLCall(glGenerateMipmap(GL_TEXTURE_2D));

    GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_width, m_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_local_buffer));

    // // Black/white checkerboard
    // float pixels[] = {
    //     0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
    //     1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f};
    // GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 2, 2, 0, GL_RGB, GL_FLOAT, pixels));

    unbind();

    if (m_local_buffer)
    {
        // could keep around if needed but for now, delete right away
        stbi_image_free(m_local_buffer);
        m_local_buffer = 0;
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
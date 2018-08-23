#pragma once

#include "renderer.hpp"

#include <string>

class Texture
{
    unsigned int m_renderer_id;

    std::string m_filepath;

    int m_width;
    int m_height;
    int m_bpp;
    unsigned char *m_local_buffer;

  public:
    explicit Texture(std::string const &filepath);
    ~Texture();

    void bind(unsigned int slot = 0) const;
    void unbind() const;

    inline int getWidth() { return m_width; }
    inline int getHeight() { return m_height; }
};
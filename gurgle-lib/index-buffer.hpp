#pragma once

class IndexBuffer
{
    unsigned int m_renderer_id;
    unsigned int m_count;

  public:
    IndexBuffer(unsigned int const *data, unsigned int count);
    ~IndexBuffer();

    void bind() const;
    void unbind() const;

    inline unsigned int getCount() const { return m_count; }
};

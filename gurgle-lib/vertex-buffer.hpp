#pragma once

class VertexBuffer
{
    unsigned int m_renderer_id;

  public:
    VertexBuffer(void const *data, unsigned int size);
    ~VertexBuffer();

    void bind() const;
    void unbind() const;
};

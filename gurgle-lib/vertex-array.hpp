#pragma once

#include "vertex-buffer.hpp"
#include "vertex-layout.hpp"

class VertexArray
{
    unsigned int m_renderer_id;

  public:
    VertexArray();
    ~VertexArray();

    void addBuffer(VertexBuffer const &vertex_buffer, VertexLayout const &vertex_layout);
    void bind() const;
    void unbind() const;
};

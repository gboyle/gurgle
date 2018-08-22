#include "vertex-buffer.hpp"

#include "renderer.hpp"

#include <iostream>

//////////////////////////////////////////////////////////////////////////

VertexBuffer::VertexBuffer(void const *data, unsigned int size)
{
    GLCall(glGenBuffers(1, &m_renderer_id));

    bind();

    GLCall(glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW));
}

VertexBuffer::~VertexBuffer()
{
    GLCall(glDeleteBuffers(1, &m_renderer_id));
}

//////////////////////////////////////////////////////////////////////////

void VertexBuffer::bind() const
{
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_renderer_id));
}

void VertexBuffer::unbind() const
{
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
}

//////////////////////////////////////////////////////////////////////////

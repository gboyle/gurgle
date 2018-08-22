#include "index-buffer.hpp"

#include "renderer.hpp"

#include <iostream>

//////////////////////////////////////////////////////////////////////////

IndexBuffer::IndexBuffer(unsigned int const *data, unsigned int count) : m_count(count)
{
    ASSERT(sizeof(unsigned int) == sizeof(GLuint));

    GLCall(glGenBuffers(1, &m_renderer_id));

    bind();

    GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_count * sizeof(unsigned int), data, GL_STATIC_DRAW));
}

IndexBuffer::~IndexBuffer()
{
    GLCall(glDeleteBuffers(1, &m_renderer_id));
}

//////////////////////////////////////////////////////////////////////////

void IndexBuffer::bind() const
{
    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_renderer_id));
}

void IndexBuffer::unbind() const
{
    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
}

//////////////////////////////////////////////////////////////////////////

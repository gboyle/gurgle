
#include "renderer.hpp"
#include "vertex-array.hpp"

//////////////////////////////////////////////////////////////////////////

VertexArray::VertexArray()
{
    GLCall(glGenVertexArrays(1, &m_renderer_id));
}
VertexArray::~VertexArray()
{
    GLCall(glDeleteVertexArrays(1, &m_renderer_id));
}

//////////////////////////////////////////////////////////////////////////

void VertexArray::addBuffer(VertexBuffer const &vertex_buffer, VertexLayout const &vertex_layout)
{
    bind();
    vertex_buffer.bind();

    const auto &elements = vertex_layout.getElements();

    for (unsigned int i = 0; i < elements.size(); i++)
    {
        const auto &element = elements[i];

        GLCall(glEnableVertexAttribArray(i));
        GLCall(glVertexAttribPointer(i, element.count, element.type, element.normalized, vertex_layout.getStride(), (const void *)element.offset));
    }
}

void VertexArray::bind() const
{
    GLCall(glBindVertexArray(m_renderer_id));
}

void VertexArray::unbind() const
{
    GLCall(glBindVertexArray(0));
}

//////////////////////////////////////////////////////////////////////////

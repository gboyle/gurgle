
#include "vertex-layout.hpp"

//////////////////////////////////////////////////////////////////////////

VertexElement::VertexElement(unsigned int type, unsigned int offset, unsigned int count, unsigned char normalized)
    : type(type), offset(offset), count(count), normalized(normalized)
{
}

//////////////////////////////////////////////////////////////////////////

VertexLayout::VertexLayout()
    : m_stride(0)
{
}
VertexLayout::~VertexLayout()
{
}

//////////////////////////////////////////////////////////////////////////

void VertexLayout::pushFloat(unsigned int count)
{
    m_elements.emplace_back(GL_FLOAT, m_stride, count, GL_FALSE);
    m_stride += sizeof(GLfloat) * count;
}

void VertexLayout::pushUnsignedInt(unsigned int count)
{
    m_elements.emplace_back(GL_UNSIGNED_INT, m_stride, count, GL_FALSE);
    m_stride += sizeof(GLuint) * count;
}

void VertexLayout::pushUnsignedChar(unsigned int count)
{
    m_elements.emplace_back(GL_UNSIGNED_BYTE, m_stride, count, GL_TRUE);
    m_stride += sizeof(GLbyte) * count;
}

//////////////////////////////////////////////////////////////////////////

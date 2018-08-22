#pragma once

#include <GL/glew.h>

#include <vector>

struct VertexElement
{
    unsigned int type;
    unsigned int offset;
    unsigned int count;
    unsigned char normalized;

    VertexElement(unsigned int type, unsigned int offset, unsigned int count, unsigned char normalized);
};

class VertexLayout
{
    unsigned int m_stride;
    std::vector<VertexElement> m_elements;

  public:
    VertexLayout();
    ~VertexLayout();

    void pushFloat(unsigned int count);
    void pushUnsignedInt(unsigned int count);
    void pushUnsignedChar(unsigned int count);

    inline unsigned int getStride() const { return m_stride; }
    inline const std::vector<VertexElement> &getElements() const { return m_elements; }
};

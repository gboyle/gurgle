#pragma once

class VertexBuffer
{
  unsigned int m_renderer_id;

public:
  VertexBuffer();
  ~VertexBuffer();

  void setData(void const *data, unsigned int size);
  void bind() const;
  void unbind() const;
};

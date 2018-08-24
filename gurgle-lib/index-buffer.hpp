#pragma once

class IndexBuffer
{
  unsigned int m_renderer_id;
  unsigned int m_count;

public:
  IndexBuffer();
  ~IndexBuffer();

  void setData(unsigned int const *data, unsigned int count);
  void bind() const;
  void unbind() const;

  inline unsigned int getCount() const { return m_count; }
};

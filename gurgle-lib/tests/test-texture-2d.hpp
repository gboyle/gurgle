
#include "test.hpp"
#include "texture.hpp"

namespace test
{

class TestTexture2D : public Test
{

  glm::vec3 m_translation1;
  glm::vec3 m_translation2;

  glm::mat4 m_projection_matrix;
  glm::mat4 m_view_matrix;

  VertexBuffer m_vertex_buffer;
  VertexLayout m_vertex_layout;
  VertexArray m_vertex_array;
  IndexBuffer m_index_buffer;
  Texture m_texture;
  Shader m_shader;

public:
  TestTexture2D();
  ~TestTexture2D() override;

  void onUpdate(float delta_time) override;
  void onRender(Renderer &renderer) override;
  void onGuiRender() override;
};

} // namespace test
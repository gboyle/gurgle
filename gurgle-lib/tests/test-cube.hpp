
#include "test.hpp"
#include "texture.hpp"

#include <glm/glm.hpp>

namespace test
{

class TestCube : public Test
{
    glm::vec3 m_translation;
    glm::vec3 m_rotation;
    glm::vec3 m_scale;

    glm::mat4 m_projection_matrix;
    glm::mat4 m_view_matrix;

    VertexBuffer m_vertex_buffer;
    VertexLayout m_vertex_layout;
    VertexArray m_vertex_array;
    IndexBuffer m_index_buffer;
    Shader m_shader;

  public:
    TestCube();
    ~TestCube() override;

    void onUpdate(float delta_time) override;
    void onRender(Renderer &renderer) override;
    void onGuiRender() override;
};

} // namespace test
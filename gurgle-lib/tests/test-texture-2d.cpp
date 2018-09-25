
#include "test-texture-2d.hpp"

#include "renderer.hpp"

#include "imgui.h"

namespace test
{

//////////////////////////////////////////////////////////////////////////

TestTexture2D::TestTexture2D()
    : m_translation1{200, 200, 0},
      m_translation2{400, 200, 0}
{
    float vertices[] = {
        -50.0f, -50.0f, 0.0f, 0.0f, // lower left
        +50.0f, -50.0f, 1.0f, 0.0f, // lower right
        +50.0f, +50.0f, 1.0f, 1.0f, // upper right
        -50.0f, +50.0f, 0.0f, 1.0f  // upper left
    };

    m_vertex_buffer.setData(vertices, sizeof(vertices));

    m_vertex_layout.pushFloat(2);
    m_vertex_layout.pushFloat(2);

    m_vertex_array.addBuffer(m_vertex_buffer, m_vertex_layout);

    unsigned int indices[] = {
        0, 1, 2,
        2, 3, 0};

    m_index_buffer.setData(indices, sizeof(indices));

    m_projection_matrix = glm::ortho(0.0f, 960.0f, 0.0f, 540.0f, -1.0f, +1.0f); // left right bottom top near far
    m_view_matrix = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0));

    m_texture.open("res/textures/cherno.png");
    m_texture.bind();

    m_shader.open("res/shaders/basic.glsl");
    m_shader.bind();
    m_shader.setUniform4f("u_color", 0.8f, 0.3f, 0.8f, 1.0f);
    m_shader.setUniform1i("u_texture", 0);

    // unbind everything
    m_vertex_array.unbind();
    m_shader.unbind();
    m_index_buffer.unbind();
}

TestTexture2D::~TestTexture2D()
{
}

//////////////////////////////////////////////////////////////////////////

void TestTexture2D::onUpdate(float delta_time)
{
}

void TestTexture2D::onRender(Renderer &renderer)
{
    m_shader.bind();

    {
        glm::mat4 model_matrix = glm::translate(glm::mat4(1.0f), m_translation1);
        glm::mat4 mvp_matrix = m_projection_matrix * m_view_matrix * model_matrix; // column major order => reverse order
        m_shader.setUniformMat4f("u_mvp", mvp_matrix);
        renderer.draw(m_vertex_array, m_index_buffer, m_shader);
    }

    {
        glm::mat4 model_matrix = glm::translate(glm::mat4(1.0f), m_translation2);
        glm::mat4 mvp_matrix = m_projection_matrix * m_view_matrix * model_matrix; // column major order => reverse order
        m_shader.setUniformMat4f("u_mvp", mvp_matrix);
        renderer.draw(m_vertex_array, m_index_buffer, m_shader);
    }
}

void TestTexture2D::onGuiRender()
{
    ImGui::SliderFloat3("Translation 1", &m_translation1.x, 0.0f, 960.0f);
    ImGui::SliderFloat3("Translation 2", &m_translation2.x, 0.0f, 960.0f);
    ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
}

//////////////////////////////////////////////////////////////////////////

} // namespace test

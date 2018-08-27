
#include "test-cube.hpp"

#include "renderer.hpp"
#include "shader.hpp"
#include "texture.hpp"

#include "imgui.h"

namespace test
{

//////////////////////////////////////////////////////////////////////////

TestCube::TestCube()
    : m_translation{200.0f, 200.0f, 0.0f},
      m_rotation{0.0f, 0.0f, 0.0f},
      m_scale{1.0f, 1.0f, 1.0f}
{
    float vertices[] = {
        -50.0f, -50.0f, -50.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, //    0   lower face
        +50.0f, -50.0f, -50.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, //    1
        +50.0f, -50.0f, +50.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, //    2
        -50.0f, -50.0f, +50.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, //    3
        -50.0f, +50.0f, -50.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, //    4   upper face
        +50.0f, +50.0f, -50.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, //    5
        +50.0f, +50.0f, +50.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, //    6
        -50.0f, +50.0f, +50.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, //    7
    };

    m_vertex_buffer.setData(vertices, sizeof(vertices));

    m_vertex_layout.pushFloat(3);
    m_vertex_layout.pushFloat(3);
    m_vertex_layout.pushFloat(2);

    m_vertex_array.addBuffer(m_vertex_buffer, m_vertex_layout);

    unsigned int indices[] = {
        0, 3, 2, // lower face
        2, 1, 0, //
        4, 5, 6, // upper face
        6, 7, 4, //
        0, 1, 5, // front face
        5, 4, 0, //
        2, 3, 7, // back face
        7, 6, 2, //
        4, 7, 3, // left face
        3, 0, 4, //
        1, 2, 6, // right face
        6, 5, 1  //
    };

    m_index_buffer.setData(indices, sizeof(indices));

    m_projection_matrix = glm::ortho(0.0f, 960.0f, 0.0f, 540.0f, -200.0f, +200.0f); // left right bottom top near far
    m_view_matrix = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0));

    m_shader.open("res/shaders/cube.glsl");
    m_shader.bind();

    // unbind everything
    m_vertex_array.unbind();
    m_shader.unbind();
    m_index_buffer.unbind();
}

TestCube::~TestCube()
{
}

//////////////////////////////////////////////////////////////////////////

void TestCube::onUpdate(float delta_time)
{
}

void TestCube::onRender(Renderer &renderer)
{
    m_shader.bind();

    glm::mat4 trans = glm::translate(glm::mat4(1.0f), m_translation);
    glm::mat4 rot1 = glm::rotate(trans, m_rotation.x, glm::vec3(0.0f, 1.0f, 0.0f));
    glm::mat4 rot2 = glm::rotate(rot1, m_rotation.y, glm::vec3(1.0f, 0.0f, 0.0f));
    glm::mat4 rot3 = glm::rotate(rot2, m_rotation.z, glm::vec3(0.0f, 0.0f, 1.0f));
    glm::mat4 model_matrix = glm::scale(rot3, m_scale);
    glm::mat4 mvp_matrix = m_projection_matrix * m_view_matrix * model_matrix; // column major order => reverse order

    m_shader.setUniformMat4f("u_mvp", mvp_matrix);

    renderer.draw(m_vertex_array, m_index_buffer, m_shader);
}

void TestCube::onGuiRender()
{
    ImGui::SliderFloat3("Translation", &m_translation.x, 0.0f, 960.0f);
    ImGui::SliderFloat3("Rotation", &m_rotation.x, 0.0f, 7.0f);
    ImGui::SliderFloat3("Scale", &m_scale.x, 0.0f, 10.0f);
    ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
}

//////////////////////////////////////////////////////////////////////////

} // namespace test

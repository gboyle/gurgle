
#include "test-clear-color.hpp"

#include "renderer.hpp"

#include "imgui.h"

namespace test
{

//////////////////////////////////////////////////////////////////////////

TestClearColor::TestClearColor()
    : m_clear_color{0.2f, 0.3f, 0.8f, 1.0f}
{
}

TestClearColor::~TestClearColor()
{
}

//////////////////////////////////////////////////////////////////////////

void TestClearColor::onUpdate(float delta_time)
{
}

void TestClearColor::onRender(Renderer &renderer)
{
    GLCall(glClearColor(m_clear_color[0], m_clear_color[1], m_clear_color[2], m_clear_color[3]));
    GLCall(glClear(GL_COLOR_BUFFER_BIT));
}

void TestClearColor::onGuiRender()
{
    ImGui::ColorEdit4("Clear Color", m_clear_color);
}

//////////////////////////////////////////////////////////////////////////

} // namespace test

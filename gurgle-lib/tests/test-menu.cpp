
#include "test-menu.hpp"

#include "imgui.h"

namespace test
{
//////////////////////////////////////////////////////////////////////////

TestMenu::TestMenu(Test *&current_test)
    : m_current_test(current_test)
{
}

TestMenu::~TestMenu()
{
}

//////////////////////////////////////////////////////////////////////////

void TestMenu::onGuiRender()
{
    for (auto &test : m_test_collection)
    {
        if (ImGui::Button(test.first.c_str()))
        {
            m_current_test = test.second();
            break;
        };
    }
}

//////////////////////////////////////////////////////////////////////////

} // namespace test

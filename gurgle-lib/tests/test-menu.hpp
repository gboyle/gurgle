#pragma once

#include "test.hpp"

#include <vector>
#include <string>
#include <functional>

namespace test
{

class TestMenu : public Test
{
    Test *&m_current_test;
    std::vector<std::pair<std::string, std::function<Test *()>>> m_test_collection;

  public:
    TestMenu(Test *&current_test);
    ~TestMenu() override;

    void onGuiRender() override;

    template <typename T>
    void registerTest(std::string const &name)
    {
        m_test_collection.push_back(std::make_pair(name, []() { return new T(); }));
    }
};

} // namespace test
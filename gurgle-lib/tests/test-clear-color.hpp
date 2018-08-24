
#include "test.hpp"

namespace test
{

class TestClearColor : public Test
{

  float m_clear_color[4];

public:
  TestClearColor();
  ~TestClearColor() override;

  void onUpdate(float delta_time) override;
  void onRender(Renderer &renderer) override;
  void onGuiRender() override;
};

} // namespace test
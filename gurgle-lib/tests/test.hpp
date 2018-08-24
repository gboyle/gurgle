#pragma once

#include "renderer.hpp"

namespace test
{

class Test
{
public:
  Test() {}
  virtual ~Test() {}

  virtual void onUpdate(float delta_time) {}
  virtual void onRender(Renderer &renderer) {}
  virtual void onGuiRender() {}
};

} // namespace test
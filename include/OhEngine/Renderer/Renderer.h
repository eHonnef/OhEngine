#pragma once

#include "Scene.h"
#include "Window.h"

namespace OhEngine {

class Renderer {
private:
  Window *m_Window;
  Scene *m_Scene;

public:
  Renderer();
  ~Renderer();

  void render();
};

} // namespace OhEngine

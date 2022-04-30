#include <OhEngine/Renderer/Renderer.h>

namespace OhEngine {

Renderer::Renderer() {
  m_Window = new Window();
  m_Scene = new Scene();
}

Renderer::~Renderer() {
  delete m_Window;
  delete m_Scene;
}

void Renderer::render() {
  while (!m_Window->shouldClose()) {
    m_Window->process();
  }
}
} // namespace OhEngine

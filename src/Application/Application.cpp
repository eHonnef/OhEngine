#include <OhEngine/Application/Application.h>
#include <OhEngine/Renderer/Renderer.h>

namespace OhEngine {

Application::Application() {}

Application::~Application() {}

void Application::run() {
  Renderer Renderer;
  Renderer.render();
}

} // namespace OhEngine

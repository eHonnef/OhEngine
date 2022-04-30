#include <OhEngine/Renderer/Window.h>
#include <OhEngine/Utils/Globals.h>
#include <exception>

namespace OhEngine {

Window::Window() {
  // Initializing window and configuring
  glfwInit();

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, OPENGL_VERSION_MAJOR);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, OPENGL_VERSION_MINOR);

  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  // Window creation
  m_GLFWwindow = glfwCreateWindow(800, 800, "Teste", nullptr, nullptr);
  if (m_GLFWwindow == nullptr) {
    glfwTerminate();
    throw std::bad_typeid();
  }
  glfwMakeContextCurrent(m_GLFWwindow);
  glfwSetFramebufferSizeCallback(m_GLFWwindow, onWindowResize);

  gladLoadGL();

  glViewport(0, 0, 800, 800);
}

Window::~Window() {
  glfwDestroyWindow(m_GLFWwindow);
  glfwTerminate();

  m_GLFWwindow = nullptr;
}

void Window::process() {
  processWindowInput();

  glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT);

  glfwSwapBuffers(m_GLFWwindow);
  glfwPollEvents();
}

void Window::onWindowResize(GLFWwindow *Window, int nWidth, int nHeight) {
  UNUSED(Window);
  glViewport(0, 0, nWidth, nHeight);
}

void Window::processWindowInput() {
  if (glfwGetKey(m_GLFWwindow, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    glfwSetWindowShouldClose(m_GLFWwindow, true);
}
} // namespace OhEngine

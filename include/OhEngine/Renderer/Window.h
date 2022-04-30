#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace OhEngine {

class Window {
protected:
  GLFWwindow *m_GLFWwindow;

  /// (GLFW)Window callback events
  void processWindowInput();
  static void onWindowResize(GLFWwindow *Window, int nWidth, int nHeight);

public:
  Window();
  ~Window();

  bool shouldClose() { return glfwWindowShouldClose(m_GLFWwindow); }
  void process();
};

} // namespace OhEngine

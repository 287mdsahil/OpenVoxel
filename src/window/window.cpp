#include "window.h"

OpenVoxelWindow::OpenVoxelWindow() { init(); }

void OpenVoxelWindow::init() {
  GlCall(glfwInit());
  GlCall(glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3));
  GlCall(glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3));
  GlCall(glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE));
  GlCall(glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE));

  GlCall(m_window = glfwCreateWindow(m_window_width, m_window_height, "OpenVoxel",
                                   nullptr, nullptr));
  if (m_window == nullptr) {
    std::cout << "Failed to create GLFW window" << std::endl;
    GlCall(glfwTerminate());
    return;
  }
  GlCall(glfwMakeContextCurrent(m_window));

  // Initialize GLEW
  glewExperimental = GL_TRUE;
  if (glewInit() != GLEW_OK) {
    std::cout << "Failed to initialize GLEW" << std::endl;
    return;
  }
  GlCall(glClearColor(0.2f, 0.3f, 0.4f, 1.0f));
  GlCall(glViewport(0, 0, m_window_width, m_window_height));
  GlCall(glfwSwapInterval(1));
  GlCall(glEnable(GL_DEPTH_TEST));
}
GLFWwindow *OpenVoxelWindow::getWindow() { return m_window; }
bool OpenVoxelWindow::should_close() { return glfwWindowShouldClose(m_window); }
void OpenVoxelWindow::swap_buffers() {
  // Swap the buffers
  GlCall(glfwSwapBuffers(m_window));
}
int OpenVoxelWindow::getHeight() { return m_window_height; }
int OpenVoxelWindow::getWidth() { return m_window_width; }

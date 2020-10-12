#include "window.h"

OpenVoxelWindow::OpenVoxelWindow() { init(); }

void OpenVoxelWindow::init() {
  GlCall(glfwInit());
  GlCall(glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3));
  GlCall(glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3));
  GlCall(glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE));
  GlCall(glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE));

  GlCall(window = glfwCreateWindow(window_width, window_height, "OpenVoxel",
                                   nullptr, nullptr));
  if (window == nullptr) {
    std::cout << "Failed to create GLFW window" << std::endl;
    GlCall(glfwTerminate());
    return;
  }
  GlCall(glfwMakeContextCurrent(window));

  // Initialize GLEW
  glewExperimental = GL_TRUE;
  if (glewInit() != GLEW_OK) {
    std::cout << "Failed to initialize GLEW" << std::endl;
    return;
  }
  GlCall(glClearColor(0.2f, 0.3f, 0.4f, 1.0f));
  GlCall(glViewport(0, 0, window_width, window_height));
  GlCall(glfwSwapInterval(1));
  GlCall(glEnable(GL_DEPTH_TEST));
}
GLFWwindow *OpenVoxelWindow::getWindow() { return window; }
bool OpenVoxelWindow::should_close() { return glfwWindowShouldClose(window); }
void OpenVoxelWindow::swap_buffers() {
  // Swap the buffers
  GlCall(glfwSwapBuffers(window));
}
int OpenVoxelWindow::getHeight() { return window_height; }
int OpenVoxelWindow::getWidth() { return window_width; }

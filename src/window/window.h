#define GLEW_STATIC
#include "../error_handling/errorHandling.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

class OpenVoxelWindow {
  int window_height = 600;
  int window_width = 800;
  GLFWwindow *window;

  void init() {
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

public:
  OpenVoxelWindow() { init(); }
  GLFWwindow *getWindow() { return window; }
  bool should_close() { return glfwWindowShouldClose(window); }
  void swap_buffers() {
    // Swap the buffers
    GlCall(glfwSwapBuffers(window));
  }
  int getHeight() { return window_height; }
  int getWidth() { return window_width; }
};

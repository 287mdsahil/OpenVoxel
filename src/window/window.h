#define GLEW_STATIC
#include "../error_handling/errorHandling.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

class OpenVoxelWindow {
  int m_window_height = 600;
  int m_window_width = 800;
  GLFWwindow *m_window;
  void init();

public:
  OpenVoxelWindow();
  GLFWwindow *getWindow();
  bool should_close();
  void swap_buffers();
  int getHeight();
  int getWidth();
};

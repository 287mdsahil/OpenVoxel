#define GLEW_STATIC
#include "../error_handling/errorHandling.h"
#include "../vendor/glm/glm.hpp"
#include "../vendor/glm/gtc/matrix_transform.hpp"
#include "../vendor/glm/gtc/type_ptr.hpp"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

class OpenVoxelWindow {
  int m_window_height = 600;
  int m_window_width = 800;
  GLFWwindow *m_window;
  void init();
  glm::mat4 m_projection;

public:
  OpenVoxelWindow();
  GLFWwindow *getWindow();
  bool should_close();
  void swap_buffers();
  int getHeight();
  int getWidth();
  glm::mat4 getProjection();
  void window_resize_callback(int width, int height);
};

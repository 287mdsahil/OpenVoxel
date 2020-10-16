#define GLEW_STATIC
#include "camera/camera.h"
#include "error_handling/errorHandling.h"
#include "renderer/renderer.h"
#include "texture/texture.h"
#include "vendor/glm/glm.hpp"
#include "vendor/glm/gtc/matrix_transform.hpp"
#include "vendor/glm/gtc/type_ptr.hpp"
#include "vendor/stb_image/stb_image.h"
#include "window/window.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

bool keys[1024];
float lastX = 0;
float lastY = 0;
float yaw = 0.0f;
float pitch = 0.0f;
bool firstMouse = true;
bool cursor_captured = GLFW_FALSE;
OpenVoxelWindow window;
glm::mat4 projection;

void error_callback(int error, const char *description) {
  fprintf(stderr, "Error: %s\n", description);
}

void key_callback(GLFWwindow *window, int key, int scancode, int action,
                  int mode) {
  if (action == GLFW_PRESS)
    keys[key] = true;
  else if (action == GLFW_RELEASE)
    keys[key] = false;

  if (key == GLFW_KEY_ESCAPE) {
    glfwSetWindowShouldClose(window, true);
  }
  if (key == GLFW_KEY_TAB && action == GLFW_PRESS) {
    if (cursor_captured) {
      cursor_captured = GLFW_FALSE;
      GlCall(glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL));
      firstMouse = true;

    } else {
      cursor_captured = GLFW_TRUE;
      GlCall(glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED));
    }
  }
}

void mouse_callback(GLFWwindow *window, double xpos, double ypos) {
  if (cursor_captured) {
    if (firstMouse) {
      lastX = xpos;
      lastY = ypos;
      firstMouse = false;
    } else {
      float sensitivity = 0.05f;
      float xoffset = (xpos - lastX) * sensitivity;
      float yoffset = (ypos - lastY) * sensitivity;
      lastX = xpos;
      lastY = ypos;
      yaw += xoffset;
      pitch -= yoffset;

      if (pitch > 89.0f)
        pitch = 89.0f;
      if (pitch < -89.0f)
        pitch = -89.0f;
    }
  }
};

void window_resize_callback(GLFWwindow *w, int width, int height) {
  window.window_resize_callback(width, height);
  projection = window.getProjection();
}

int main() {
  GlCall(glfwSetKeyCallback(window.getWindow(), key_callback));
  GlCall(glfwSetCursorPosCallback(window.getWindow(), mouse_callback));
  GlCall(glfwSetFramebufferSizeCallback(window.getWindow(),
                                        window_resize_callback));
  GlCall(glfwSetInputMode(window.getWindow(), GLFW_CURSOR, GLFW_CURSOR_NORMAL));
  Renderer voxel_renderer;

  Camera camera;
  projection = window.getProjection();

  // Setting the clear color
  GlCall(glClearColor(0.2f, 0.3f, 0.4f, 1.0f));
  // Game loop
  while (!window.should_close()) {
    GlCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
    // Check and call events
    GlCall(glfwPollEvents());

    camera.do_movement(keys, pitch, yaw);

    // Rendering
    voxel_renderer.bind();
    // basic_shader.bind();
    glm::mat4 view = camera.getView();
    voxel_renderer.renderChunk(window.getProjection(), view);

    // Swap the buffers
    window.swap_buffers();
  }
  return 0;
}

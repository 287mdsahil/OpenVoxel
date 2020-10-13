#define GLEW_STATIC
#include "camera/camera.h"
#include "error_handling/errorHandling.h"
#include "texture/texture.h"
#include "vendor/glm/glm.hpp"
#include "vendor/glm/gtc/matrix_transform.hpp"
#include "vendor/glm/gtc/type_ptr.hpp"
#include "vendor/stb_image/stb_image.h"
#include "voxel/voxel.h"
#include "window/window.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

bool keys[1024];
float lastX = 0;
;
float lastY = 0;
float yaw = 0.0f;
float pitch = 0.0f;
bool firstMouse = true;

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
}

void mouse_callback(GLFWwindow *window, double xpos, double ypos) {
  if (firstMouse) {
    lastX = xpos;
    lastY = ypos;
    firstMouse = false;
  }

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
};

int main() {
  OpenVoxelWindow window;
  GlCall(glfwSetKeyCallback(window.getWindow(), key_callback));
  GlCall(glfwSetCursorPosCallback(window.getWindow(), mouse_callback));
  GlCall(
      glfwSetInputMode(window.getWindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED));
  Voxel voxel_element;
  voxel_element.bind();
  Shader basic_shader("src/basicVertex.shader", "src/basicFragment.shader");
  Texture grass_block_texture("./res/textures/grass_block_sprite.png");
  voxel_element.unbind();

  glm::vec3 voxel_positions[] = {
      glm::vec3(0.0f, 0.0f, 0.0f),   glm::vec3(1.0f, 0.0f, 0.0f),
      glm::vec3(-1.0f, 0.0f, 0.0f),  glm::vec3(0.0f, 0.0f, 1.0f),
      glm::vec3(0.0f, 0.0f, -1.0f),  glm::vec3(1.0f, 0.0f, 1.0f),
      glm::vec3(1.0f, 0.0f, -1.0f),  glm::vec3(-1.0f, 0.0f, 1.0f),
      glm::vec3(-1.0f, 0.0f, -1.0f),
  };

  Camera camera;
  glm::mat4 model =
      glm::rotate(glm::mat4(1.0f), -45.0f, glm::vec3(1.0f, 0.0f, 0.0f));
  glm::mat4 projection;
  projection = glm::perspective(
      45.0f, (float)window.getWidth() / (float)window.getWidth(), 1.0f,
      -100.0f);

  // Setting the clear color
  GlCall(glClearColor(0.2f, 0.3f, 0.4f, 1.0f));
  // Game loop
  while (!window.should_close()) {
    GlCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
    // Check and call events
    GlCall(glfwPollEvents());

    camera.do_movement(keys, pitch, yaw);

    // Rendering
    voxel_element.bind();
    basic_shader.bind();
    glm::mat4 view = camera.getView();
    for (glm::vec3 pos : voxel_positions) {
      model = glm::translate(glm::mat4(1.0f), pos);
      basic_shader.SetUniformMat4f("model", model);
      basic_shader.SetUniformMat4f("projection", projection);
      basic_shader.SetUniformMat4f("view", view);
      grass_block_texture.bind();
      voxel_element.render();
    }
    grass_block_texture.unbind();
    basic_shader.unbind();
    voxel_element.unbind();

    // Swap the buffers
    window.swap_buffers();
  }
  return 0;
}

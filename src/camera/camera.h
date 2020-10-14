#define GLEW_STATIC
#include "../error_handling/errorHandling.h"
#include "../vendor/glm/glm.hpp"
#include "../vendor/glm/gtc/matrix_transform.hpp"
#include "../vendor/glm/gtc/type_ptr.hpp"
#include "../vendor/stb_image/stb_image.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

class Camera {
private:
  glm::vec3 m_cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
  glm::vec3 m_cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
  glm::vec3 m_cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
  glm::mat4 m_view = glm::lookAt(m_cameraPos, m_cameraPos + m_cameraFront, m_cameraUp);
  float deltaTime = 0.0f;
  float lastFrame = 0.0f;

public:
  void do_movement(bool keys[], float pitch, float yaw) {
    // camera control
    float currentFrame = glfwGetTime();
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;

    GLfloat cameraSpeed = 5.0f * deltaTime;
    if (keys[GLFW_KEY_W])
      m_cameraPos += cameraSpeed * m_cameraFront;
    if (keys[GLFW_KEY_S])
      m_cameraPos -= cameraSpeed * m_cameraFront;
    if (keys[GLFW_KEY_A])
      m_cameraPos -=
          glm::normalize(glm::cross(m_cameraFront, m_cameraUp)) * cameraSpeed;
    if (keys[GLFW_KEY_D])
      m_cameraPos +=
          glm::normalize(glm::cross(m_cameraFront, m_cameraUp)) * cameraSpeed;

    glm::vec3 front;
    front.x = cos(glm::radians(pitch)) * cos(glm::radians(yaw));
    front.y = sin(glm::radians(pitch));
    front.z = cos(glm::radians(pitch)) * sin(glm::radians(yaw));
    m_cameraFront = glm::normalize(front);
    m_view = glm::lookAt(m_cameraPos, m_cameraPos + m_cameraFront, m_cameraUp);
  }

  glm::mat4 getView() { return m_view; }
};

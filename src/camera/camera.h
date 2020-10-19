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
  glm::vec3 m_camera_pos = glm::vec3(0.0f, 0.0f, 3.0f);
  glm::vec3 m_camera_front = glm::vec3(0.0f, 0.0f, -1.0f);
  glm::vec3 m_camera_up = glm::vec3(0.0f, 1.0f, 0.0f);
  glm::mat4 m_view = glm::lookAt(m_camera_pos, m_camera_pos + m_camera_front, m_camera_up);
  float deltaTime = 0.0f;
  float lastFrame = 0.0f;

public:
  void doMovement(bool keys[], float pitch, float yaw) {
    // camera control
    float currentFrame = glfwGetTime();
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;

    GLfloat cameraSpeed = 5.0f * deltaTime;
    if (keys[GLFW_KEY_W])
      m_camera_pos += cameraSpeed * m_camera_front;
    if (keys[GLFW_KEY_S])
      m_camera_pos -= cameraSpeed * m_camera_front;
    if (keys[GLFW_KEY_A])
      m_camera_pos -=
          glm::normalize(glm::cross(m_camera_front, m_camera_up)) * cameraSpeed;
    if (keys[GLFW_KEY_D])
      m_camera_pos +=
          glm::normalize(glm::cross(m_camera_front, m_camera_up)) * cameraSpeed;

    glm::vec3 front;
    front.x = cos(glm::radians(pitch)) * cos(glm::radians(yaw));
    front.y = sin(glm::radians(pitch));
    front.z = cos(glm::radians(pitch)) * sin(glm::radians(yaw));
    m_camera_front = glm::normalize(front);
    m_view = glm::lookAt(m_camera_pos, m_camera_pos + m_camera_front, m_camera_up);
  }

  glm::mat4 getView() { return m_view; }
};

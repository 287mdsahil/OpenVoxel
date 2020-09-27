#define GLEW_STATIC
#include "error_handling/errorHandling.h"
#include "vendor/glm/glm.hpp"
#include "vendor/glm/gtc/matrix_transform.hpp"
#include "vendor/glm/gtc/type_ptr.hpp"
#include "vendor/stb_image/stb_image.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

#define WINDOW_HEIGHT 600
#define WINDOW_WIDTH 800

glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
bool keys[1024];
float deltaTime = 0.0f;
float lastFrame = 0.0f;
float lastX = WINDOW_WIDTH / 2;
float lastY = WINDOW_HEIGHT / 2;
float yaw = 0.0f;
float pitch = 0.0f;
bool firstMouse = true;

// error callback function
void error_callback(int error, const char *description) {
  fprintf(stderr, "Error: %s\n", description);
}

void do_movement() {
  // camera control
  GLfloat cameraSpeed = 5.0f * deltaTime;
  if (keys[GLFW_KEY_W])
    cameraPos += cameraSpeed * cameraFront;
  if (keys[GLFW_KEY_S])
    cameraPos -= cameraSpeed * cameraFront;
  if (keys[GLFW_KEY_A])
    cameraPos -=
        glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
  if (keys[GLFW_KEY_D])
    cameraPos +=
        glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
}

void key_callback(GLFWwindow *window, int key, int scancode, int action,
                  int mode) {
  // Set WindowShouldClose property to true if 'Q' is pressed
  if (key == GLFW_KEY_Q && action == GLFW_PRESS) {
    GlCall(glfwSetWindowShouldClose(window, GL_TRUE));
  }

  if (action == GLFW_PRESS)
    keys[key] = true;
  else if (action == GLFW_RELEASE)
    keys[key] = false;
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

std::string parseShader(std::string filepath) {
  std::stringstream source;
  std::ifstream sourcefile(filepath);
  std::string line;
  while (getline(sourcefile, line)) {
    source << line << "\n";
  }
  return source.str();
}

GLuint makeTexture(std::string filename) {
  stbi_set_flip_vertically_on_load(1);
  int height, width, BPP;
  unsigned char *localBuffer =
      stbi_load(filename.c_str(), &width, &height, &BPP, 4);

  GLuint texture;
  GlCall(glGenTextures(1, &texture));
  GlCall(glBindTexture(GL_TEXTURE_2D, texture));

  GlCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
  GlCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
  GlCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
  GlCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));

  GlCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA,
                      GL_UNSIGNED_BYTE, localBuffer));
  GlCall(glActiveTexture(GL_TEXTURE0));
  GlCall(glBindTexture(GL_TEXTURE_2D, 0));
  if (localBuffer)
    stbi_image_free(localBuffer);
  return texture;
}

int main() {
  GlCall(glfwInit());
  GlCall(glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3));
  GlCall(glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3));
  GlCall(glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE));
  GlCall(glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE));

  GlCall(GLFWwindow *window = glfwCreateWindow(
             WINDOW_WIDTH, WINDOW_HEIGHT, "Opengl_test_2", nullptr, nullptr));
  if (window == nullptr) {
    std::cout << "Failed to create GLFW window" << std::endl;
    GlCall(glfwTerminate());
    return -1;
  }
  GlCall(glfwMakeContextCurrent(window));

  // Initialize GLEW
  glewExperimental = GL_TRUE;
  if (glewInit() != GLEW_OK) {
    std::cout << "Failed to initialize GLEW" << std::endl;
    return -1;
  }

  // Set the key and cursor callback function
  GlCall(glfwSetKeyCallback(window, key_callback));
  GlCall(glfwSetCursorPosCallback(window, mouse_callback));

  // Set error callbakc function
  GlCall(glfwSetErrorCallback(error_callback));

  // Setting size of rendering window
  GlCall(glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT));
  GlCall(glfwSwapInterval(1));
  GlCall(glEnable(GL_DEPTH_TEST));
  GlCall(glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED));

  // Vertex Shader
  GLuint vertexShader;
  GlCall(vertexShader = glCreateShader(GL_VERTEX_SHADER));
  std::string vertexShaderSource =
      parseShader("./src/shaders/basicVertex.shader");
  const char *vertexShaderSrc = vertexShaderSource.c_str();
  GlCall(glShaderSource(vertexShader, 1, &vertexShaderSrc, nullptr));
  GlCall(glCompileShader(vertexShader));
  // Check for compilation errors
  int success;
  char infoLog[512];
  GlCall(glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success));
  if (!success) {
    GlCall(glGetShaderInfoLog(vertexShader, 512, NULL, infoLog));
    std::cout << "Error: vertex shader compilation failed" << std::endl
              << infoLog << std::endl;
  }

  // Fragment Shader
  GLuint fragmentShader;
  GlCall(fragmentShader = glCreateShader(GL_FRAGMENT_SHADER));
  std::string fragmentShaderSource =
      parseShader("./src/shaders/basicFragment.shader");
  const char *fragmentShaderSrc = fragmentShaderSource.c_str();
  GlCall(glShaderSource(fragmentShader, 1, &fragmentShaderSrc, nullptr));
  GlCall(glCompileShader(fragmentShader));
  // Check for compilation errors
  GlCall(glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success));
  if (!success) {
    GlCall(glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog));
    std::cout << "Error: fragment shader compilation failed" << std::endl
              << infoLog << std::endl;
  }

  // linking shaders
  GLuint shaderProgram;
  GlCall(shaderProgram = glCreateProgram());
  GlCall(glAttachShader(shaderProgram, vertexShader));
  GlCall(glAttachShader(shaderProgram, fragmentShader));
  GlCall(glLinkProgram(shaderProgram));
  // Check for compilation errors
  GlCall(glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success));
  if (!success) {
    GlCall(glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog));
    std::cout << "Error: shader programs linking failed" << std::endl
              << infoLog << std::endl;
  }

  // binding the shader program
  GlCall(glUseProgram(shaderProgram));
  GlCall(glDeleteShader(vertexShader));
  GlCall(glDeleteShader(fragmentShader));

  /*
  GLfloat vertices[] = {
      // posiiton         // Texture coords
      0.5f,  0.5f,  0.0f, 1.0f, 1.0f, // 0 top right front
      -0.5f, 0.5f,  0.0f, 0.0f, 1.0f, // 1 top left front
      -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, // 2 bottom left front
      0.5f,  -0.5f, 0.0f, 1.0f, 0.0f, // 3 bottom right front
  };
  GLuint indices[] = {
      //first rect
      0, 1, 2, // first triangle
      2, 3, 0  // second triangle
  };
  */
  float vertices[] = {
      -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, //
      0.5f, -0.5f, -0.5f, 1.0f, 0.0f,  //
      0.5f, 0.5f, -0.5f, 1.0f, 1.0f,   //
      0.5f, 0.5f, -0.5f, 1.0f, 1.0f,   //
      -0.5f, 0.5f, -0.5f, 0.0f, 1.0f,  //
      -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, //
                                       //
      -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,  //
      0.5f, -0.5f, 0.5f, 1.0f, 0.0f,   //
      0.5f, 0.5f, 0.5f, 1.0f, 1.0f,    //
      0.5f, 0.5f, 0.5f, 1.0f, 1.0f,    //
      -0.5f, 0.5f, 0.5f, 0.0f, 1.0f,   //
      -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,  //
                                       //
      -0.5f, 0.5f, 0.5f, 1.0f, 0.0f,   //
      -0.5f, 0.5f, -0.5f, 1.0f, 1.0f,  //
      -0.5f, -0.5f, -0.5f, 0.0f, 1.0f, //
      -0.5f, -0.5f, -0.5f, 0.0f, 1.0f, //
      -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,  //
      -0.5f, 0.5f, 0.5f, 1.0f, 0.0f,   //
                                       //
      0.5f, 0.5f, 0.5f, 1.0f, 0.0f,    //
      0.5f, 0.5f, -0.5f, 1.0f, 1.0f,   //
      0.5f, -0.5f, -0.5f, 0.0f, 1.0f,  //
      0.5f, -0.5f, -0.5f, 0.0f, 1.0f,  //
      0.5f, -0.5f, 0.5f, 0.0f, 0.0f,   //
      0.5f, 0.5f, 0.5f, 1.0f, 0.0f,    //
                                       //
      -0.5f, -0.5f, -0.5f, 0.0f, 1.0f, //
      0.5f, -0.5f, -0.5f, 1.0f, 1.0f,  //
      0.5f, -0.5f, 0.5f, 1.0f, 0.0f,   //
      0.5f, -0.5f, 0.5f, 1.0f, 0.0f,   //
      -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,  //
      -0.5f, -0.5f, -0.5f, 0.0f, 1.0f, //
                                       //
      -0.5f, 0.5f, -0.5f, 0.0f, 1.0f,  //
      0.5f, 0.5f, -0.5f, 1.0f, 1.0f,   //
      0.5f, 0.5f, 0.5f, 1.0f, 0.0f,    //
      0.5f, 0.5f, 0.5f, 1.0f, 0.0f,    //
      -0.5f, 0.5f, 0.5f, 0.0f, 0.0f,   //
      -0.5f, 0.5f, -0.5f, 0.0f, 1.0f   //
  };

  glm::vec3 cubePositions[] = {
      glm::vec3(0.0f, 0.0f, 0.0f),    glm::vec3(3.7f, 2.0f, -2.0f),
      glm::vec3(-3.5f, 0.0f, -3.0f),  glm::vec3(-10.8f, 7.0f, -10.0f),
      glm::vec3(5.0f, 1.0f, -10.0f),  glm::vec3(-0.5f, 0.0f, -20.0f),
      glm::vec3(6.0f, -1.1f, -5.0f),  glm::vec3(-10.8f, -16.0f, -10.0f),
      glm::vec3(-4.5f, -3.0f, -7.0f), glm::vec3(0.7f, 0.0f, -6.0f),
  };

  GLuint vao;
  GlCall(glGenVertexArrays(1, &vao));
  GLuint vbo;
  GlCall(glGenBuffers(1, &vbo));
  // GLuint ebo;
  // GlCall(glGenBuffers(1, &ebo));
  GlCall(glBindVertexArray(vao));
  GlCall(glBindBuffer(GL_ARRAY_BUFFER, vbo));
  GlCall(glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices,
                      GL_STATIC_DRAW));
  // GlCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo));
  // GlCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices,
  //                   GL_STATIC_DRAW));
  GlCall(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat),
                               (GLvoid *)0));
  GlCall(glEnableVertexAttribArray(0));
  GlCall(glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat),
                               (GLvoid *)(3 * sizeof(GLfloat))));
  GlCall(glEnableVertexAttribArray(1));
  GlCall(glBindVertexArray(0));

  //---------------------------
  glm::mat4 view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
  glm::mat4 model =
      glm::rotate(glm::mat4(1.0f), -45.0f, glm::vec3(1.0f, 0.0f, 0.0f));
  glm::mat4 projection;
  projection = glm::perspective(
      45.0f, (float)WINDOW_WIDTH / (float)WINDOW_HEIGHT, 1.0f, -100.0f);
  // projection = glm::ortho(0.0f, 800.0f, 0.0f, 600.0f, 0.1f, 100.0f);

  GlCall(GLint modelLoc = glGetUniformLocation(shaderProgram, "model"));
  GlCall(GLint projectionLoc =
             glGetUniformLocation(shaderProgram, "projection"));
  GlCall(GLint viewLoc = glGetUniformLocation(shaderProgram, "view"));

  GlCall(glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model)));
  GlCall(glUniformMatrix4fv(projectionLoc, 1, GL_FALSE,
                            glm::value_ptr(projection)));
  GlCall(glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view)));

  // textures-----------------
  GLuint texture = makeTexture("./res/textures/grass_block.jpeg");

  // Setting the clear color
  GlCall(glClearColor(0.2f, 0.3f, 0.4f, 1.0f));

  // Game loop
  while (!glfwWindowShouldClose(window)) {
    GlCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
    // Check and call events
    GlCall(glfwPollEvents());

    float currentFrame = glfwGetTime();
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;
    do_movement();

    // Rendering here...
    GlCall(glUseProgram(shaderProgram));
    GlCall(glActiveTexture(GL_TEXTURE0));
    GlCall(glBindTexture(GL_TEXTURE_2D, texture));
    GlCall(glBindVertexArray(vao));
    // GlCall(glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_INT, 0));
    for (GLuint i = 0; i < 10; i++) {
      model = glm::translate(glm::mat4(1.0f), cubePositions[i]);
      model = glm::rotate(model, (GLfloat)glfwGetTime() * (i + 1),
                          glm::vec3(0.5f, 0.5f, 0.5f));
      GlCall(glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model)));
      GlCall(glDrawArrays(GL_TRIANGLES, 0, 36));
    }

    glm::vec3 front;
    front.x = cos(glm::radians(pitch)) * cos(glm::radians(yaw));
    front.y = sin(glm::radians(pitch));
    front.z = cos(glm::radians(pitch)) * sin(glm::radians(yaw));
    cameraFront = glm::normalize(front);
    view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
    GlCall(glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view)));

    GlCall(glBindVertexArray(0));

    // Swap the buffers
    GlCall(glfwSwapBuffers(window));
  }

  // Clean/delete all resources
  GlCall(glDeleteProgram(shaderProgram));
  GlCall(glfwTerminate());

  return 0;
}

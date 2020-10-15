#define GLEW_STATIC
#include "../error_handling/errorHandling.h"
#include "../shader/shader.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>

class Renderer {
  unsigned int m_vao;
  unsigned int m_vbo;

public:
  Renderer();
  void bind();
  void unbind();
  void render();
};

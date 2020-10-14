#define GLEW_STATIC
#include "../error_handling/errorHandling.h"
#include "../shader/shader.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>

class Voxel {
  unsigned int m_vao;
  unsigned int m_vbo;

public:
  Voxel();
  void bind();
  void unbind();
  void render();
};

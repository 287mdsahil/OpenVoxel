#define GLEW_STATIC
#include "../chunk/chunk.h"
#include "../error_handling/errorHandling.h"
#include "../shader/shader.h"
#include "../texture/texture.h"
#include "../voxel/voxel.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <vector>

class Renderer {
  unsigned int m_vao;
  unsigned int m_vbo;
  Shader m_shader;
  Texture m_texture;
  Chunk m_chunk;
  Voxel m_voxel;

public:
  Renderer();
  void bind();
  void unbind();
  void render();
  void renderChunk(glm::mat4 projection, glm::mat4 view);
};

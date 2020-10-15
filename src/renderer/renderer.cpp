#include "renderer.h"
#include "../voxel/voxel.h"
#include <vector>

Renderer::Renderer() {
  Voxel voxel;
  std::vector<float> vertices =
      voxel.getVertices(true, true, true, true, false, false);
  GlCall(glGenVertexArrays(1, &m_vao));
  GlCall(glGenBuffers(1, &m_vbo));
  bind();
  GlCall(glBufferData(GL_ARRAY_BUFFER, sizeof(float)*4*6*5, vertices.data(),
                      GL_STATIC_DRAW));
  GlCall(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat),
                               (GLvoid *)0));
  GlCall(glEnableVertexAttribArray(0));
  GlCall(glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat),
                               (GLvoid *)(3 * sizeof(GLfloat))));
  GlCall(glEnableVertexAttribArray(1));
  unbind();
}

void Renderer::bind() {
  GlCall(glBindVertexArray(m_vao));
  GlCall(glBindBuffer(GL_ARRAY_BUFFER, m_vbo));
}

void Renderer::unbind() { GlCall(glBindVertexArray(0)); }

void Renderer::render() { GlCall(glDrawArrays(GL_TRIANGLES, 0, 6*4)); }

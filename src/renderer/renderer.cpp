#include "renderer.h"

Renderer::Renderer()
    : m_shader(Shader("src/basicVertex.shader", "src/basicFragment.shader")),
      m_texture(Texture("./res/textures/grass_block_sprite.png")) {
  GlCall(glGenVertexArrays(1, &m_vao));
  GlCall(glGenBuffers(1, &m_vbo));
  bind();
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
  m_shader.bind();
  m_texture.bind();
}

void Renderer::unbind() {
  GlCall(glBindVertexArray(0));
  m_shader.unbind();
  m_texture.unbind();
}

void Renderer::render() { GlCall(glDrawArrays(GL_TRIANGLES, 0, 6 * 4)); }

void Renderer::renderChunk(glm::mat4 projection, glm::mat4 view) {
  glm::mat4 model = glm::mat4(1.0f);
  int size = (int)m_chunk.getChunkSize();
  bind();
  for (int x = 0; x < size; x++)
    for (int y = 0; y < size; y++)
      for (int z = 0; z < size; z++) {
        if (m_chunk.getVoxelAt(x, y, z)) {
          bool front = true, rear = true, top = true, bottom = true,
               left = true, right = true;
          int faces = 6;
          if (x + 1 < size && m_chunk.getVoxelAt(x + 1, y, z)) {
            right = false;
            faces--;
          }
          if (x - 1 >= 0 && m_chunk.getVoxelAt(x - 1, y, z)) {
            left = false;
            faces--;
          }
          if (y + 1 < size && m_chunk.getVoxelAt(x, y + 1, z)) {
            top = false;
            faces--;
          }
          if (y - 1 >= 0 && m_chunk.getVoxelAt(x, y - 1, z)) {
            bottom = false;
            faces--;
          }
          if (z + 1 < size && m_chunk.getVoxelAt(x, y, z + 1)) {
            front = false;
            faces--;
          }
          if (z - 1 >= 0 && m_chunk.getVoxelAt(x, y, z - 1)) {
            rear = false;
            faces--;
          }
          if (faces > 0) {
            std::vector<float> vertices =
                m_voxel.getVertices(front, rear, top, bottom, left, right);
            GlCall(glBufferData(GL_ARRAY_BUFFER, sizeof(float) * faces * 6 * 5,
                                vertices.data(), GL_DYNAMIC_DRAW));
            glm::vec3 pos =
                m_chunk.getPos() + glm::vec3((float)x, (float)y, (float)z);
            model = glm::translate(glm::mat4(1.0f), pos);
            m_shader.SetUniformMat4f("model", model);
            m_shader.SetUniformMat4f("projection", projection);
            m_shader.SetUniformMat4f("view", view);
            GlCall(glDrawArrays(GL_TRIANGLES, 0, faces * 6));
          }
        }
      }
  unbind();
}

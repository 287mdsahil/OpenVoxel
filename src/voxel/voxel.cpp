#include "voxel.h"

Voxel::Voxel() {
  float vertices[5 * 6 * 6] = {
      -0.5f, -0.5f, -0.5f, 0.33f, 0.0f, // Rear
      0.5f, -0.5f, -0.5f, 0.67f, 0.0f,  //
      0.5f, 0.5f, -0.5f, 0.67f, 1.0f,   //
      0.5f, 0.5f, -0.5f, 0.67f, 1.0f,   //
      -0.5f, 0.5f, -0.5f, 0.33f, 1.0f,  //
      -0.5f, -0.5f, -0.5f, 0.33f, 0.0f, //
                                        //
      -0.5f, -0.5f, 0.5f, 0.33f, 0.0f,  // Front
      0.5f, -0.5f, 0.5f, .67f, 0.0f,    //
      0.5f, 0.5f, 0.5f, 0.67f, 1.0f,    //
      0.5f, 0.5f, 0.5f, 0.67f, 1.0f,    //
      -0.5f, 0.5f, 0.5f, 0.33f, 1.0f,   //
      -0.5f, -0.5f, 0.5f, 0.33f, 0.0f,  //
                                        //
      -0.5f, 0.5f, 0.5f, 0.67f, 1.0f,   // Left
      -0.5f, 0.5f, -0.5f, 0.33f, 1.0f,  //
      -0.5f, -0.5f, -0.5f, 0.33f, 0.0f, //
      -0.5f, -0.5f, -0.5f, 0.33f, 0.0f, //
      -0.5f, -0.5f, 0.5f, 0.67f, 0.0f,  //
      -0.5f, 0.5f, 0.5f, 0.67f, 1.0f,   //
                                        //
      0.5f, 0.5f, 0.5f, 0.33f, 1.0f,    // Right
      0.5f, 0.5f, -0.5f, 0.67f, 1.0f,   //
      0.5f, -0.5f, -0.5f, 0.67f, 0.0f,  //
      0.5f, -0.5f, -0.5f, 0.67f, 0.0f,  //
      0.5f, -0.5f, 0.5f, 0.33f, 0.0f,   //
      0.5f, 0.5f, 0.5f, 0.33f, 1.0f,    //
                                        //
      -0.5f, -0.5f, -0.5f, 0.67f, 0.0f, // Bottom
      0.5f, -0.5f, -0.5f, 1.0f, 0.0f,   //
      0.5f, -0.5f, 0.5f, 1.0f, 1.0f,    //
      0.5f, -0.5f, 0.5f, 1.0f, 1.0f,    //
      -0.5f, -0.5f, 0.5f, 0.67f, 1.0f,  //
      -0.5f, -0.5f, -0.5f, 0.67f, 0.0f, //
                                        //
      -0.5f, 0.5f, -0.5f, 0.0f, 1.0f,   // Top
      0.5f, 0.5f, -0.5f, 0.33f, 1.0f,   //
      0.5f, 0.5f, 0.5f, 0.33f, 0.0f,    //
      0.5f, 0.5f, 0.5f, 0.33f, 0.0f,    //
      -0.5f, 0.5f, 0.5f, 0.0f, 0.0f,    //
      -0.5f, 0.5f, -0.5f, 0.0f, 1.0f    //
  };
  GlCall(glGenVertexArrays(1, &m_vao));
  GlCall(glGenBuffers(1, &m_vbo));
  bind();
  GlCall(glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices,
                      GL_STATIC_DRAW));
  GlCall(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat),
                               (GLvoid *)0));
  GlCall(glEnableVertexAttribArray(0));
  GlCall(glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat),
                               (GLvoid *)(3 * sizeof(GLfloat))));
  GlCall(glEnableVertexAttribArray(1));
  unbind();
}

void Voxel::bind() {
  GlCall(glBindVertexArray(m_vao));
  GlCall(glBindBuffer(GL_ARRAY_BUFFER, m_vbo));
}

void Voxel::unbind() { GlCall(glBindVertexArray(0)); }

void Voxel::render() { GlCall(glDrawArrays(GL_TRIANGLES, 0, 36)); }

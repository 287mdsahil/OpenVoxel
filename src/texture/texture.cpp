#include "texture.h"
#include "../error_handling/errorHandling.h"
#include "../vendor/stb_image/stb_image.h"
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

Texture::Texture(std::string filepath)
    : m_id(0), m_filepath(filepath), m_local_buffer(nullptr), m_height(0), m_width(0),
      m_BPP(0) {
  stbi_set_flip_vertically_on_load(1);
  m_local_buffer = stbi_load(m_filepath.c_str(), &m_width, &m_height, &m_BPP, 4);

  GlCall(glGenTextures(1, &m_id));
  GlCall(glBindTexture(GL_TEXTURE_2D, m_id));

  GlCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
  GlCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
  GlCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
  GlCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));

  GlCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_width, m_height, 0, GL_RGBA,
                      GL_UNSIGNED_BYTE, m_local_buffer));
  GlCall(glActiveTexture(GL_TEXTURE0));
  GlCall(glBindTexture(GL_TEXTURE_2D, 0));
  if (m_local_buffer)
    stbi_image_free(m_local_buffer);
};

Texture::~Texture() { GlCall(glDeleteTextures(1, &m_id)); };

void Texture::bind(unsigned int slot /* = 0*/) const {
  GlCall(glActiveTexture(GL_TEXTURE0 + slot));
  GlCall(glBindTexture(GL_TEXTURE_2D, m_id));
}

void Texture::unbind() const { GlCall(glBindTexture(GL_TEXTURE_2D, 0)); }

inline int Texture::getWidth() { return m_width; }

inline int Texture::getHeight() { return m_height; }

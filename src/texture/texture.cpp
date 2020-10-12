#include "texture.h"
#include "../error_handling/errorHandling.h"
#include "../vendor/stb_image/stb_image.h"
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

Texture::Texture(std::string filepath)
    : id(0), filepath(filepath), localBuffer(nullptr), height(0), width(0),
      BPP(0) {
  stbi_set_flip_vertically_on_load(1);
  int height, width, BPP;
  unsigned char *localBuffer =
      stbi_load(filepath.c_str(), &width, &height, &BPP, 4);

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
  GlCall(glActiveTexture(GL_TEXTURE0));
  GlCall(glBindTexture(GL_TEXTURE_2D, texture));
};

Texture::~Texture() { GlCall(glDeleteTextures(1, &id)); };

void Texture::bind(unsigned int slot /* = 0*/) const {
  GlCall(glActiveTexture(GL_TEXTURE0 + slot));
  GlCall(glBindTexture(GL_TEXTURE_2D, id));
}

void Texture::unbind() const { GlCall(glBindTexture(GL_TEXTURE_2D, 0)); }

inline int Texture::getWidth() { return width; }

inline int Texture::getHeight() { return height; }

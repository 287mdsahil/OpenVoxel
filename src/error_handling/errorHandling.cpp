#include "errorHandling.h"
#include <iostream>

void GlClearError() {
  while (glGetError() != GL_NO_ERROR)
    ;
}

bool GlLogCall(const char *function, const char *file, int line) {
  if (GLenum error = glGetError()) {
    std::cout << "OpenGL Error:" << error << std::endl;
    std::cout << function << " " << file << ":" << line << std::endl;
    return false;
  }
  return true;
}

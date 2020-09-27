#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <signal.h>

#define ASSERT(x)                                                              \
  if (!(x))                                                                    \
    raise(SIGTRAP);

#define GlCall(x)                                                              \
  GlClearError();                                                              \
  x;                                                                           \
  ASSERT(GlLogCall(#x, __FILE__, __LINE__));

void GlClearError();
bool GlLogCall(const char *function, const char *file, int line);

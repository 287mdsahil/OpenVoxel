#pragma once

#include <string>

class Texture {
private:
  unsigned int id;
  std::string filepath;
  unsigned char *localBuffer;
  int width, height, BPP;

public:
  Texture(std::string filepath);
  ~Texture();
  void bind(unsigned int slot = 0) const;
  void unbind() const;
  inline int getWidth();
  inline int getHeight();
};

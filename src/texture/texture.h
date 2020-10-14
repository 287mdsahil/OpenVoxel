#pragma once

#include <string>

class Texture {
private:
  unsigned int m_id;
  std::string m_filepath;
  unsigned char *m_local_buffer;
  int m_width, m_height, m_BPP;

public:
  Texture(std::string filepath);
  ~Texture();
  void bind(unsigned int slot = 0) const;
  void unbind() const;
  inline int getWidth();
  inline int getHeight();
};

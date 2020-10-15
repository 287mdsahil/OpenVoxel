#pragma once
#include "../vendor/glm/gtc/matrix_transform.hpp"
#include "../vendor/glm/gtc/type_ptr.hpp"

class Chunk {
  unsigned int m_chunk_size;
  glm::vec3 m_chunk_pos;
  bool *m_voxel_positions;

public:
  Chunk();
  unsigned int getChunkSize();
  glm::vec3 getPos();
  bool getVoxelAt(int x, int y, int z);
  void setVoxelAt(int x, int y, int z, bool val);
};

#include "chunk.h"

Chunk::Chunk() : m_chunk_size(16), m_chunk_pos(glm::vec3(0.0f)) {
  m_voxel_positions =
      (bool *)malloc(m_chunk_size * m_chunk_size * m_chunk_size);
}

bool Chunk::getVoxelAt(int x, int y, int z) {
  int pos = x * (m_chunk_size * m_chunk_size) + y * (m_chunk_size) + z;
  return m_voxel_positions[pos];
}

void Chunk::setVoxelAt(int x, int y, int z, bool val) {
  int pos = x * (m_chunk_size * m_chunk_size) + y * (m_chunk_size) + z;
  m_voxel_positions[pos] = val;
}

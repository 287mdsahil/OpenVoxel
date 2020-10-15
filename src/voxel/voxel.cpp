#include "voxel.h"
const std::vector<float> Voxel::m_rear_face = {
    -0.5f, -0.5f, -0.5f, 0.33f, 0.0f, // Rear
    0.5f,  -0.5f, -0.5f, 0.67f, 0.0f, //
    0.5f,  0.5f,  -0.5f, 0.67f, 1.0f, //
    0.5f,  0.5f,  -0.5f, 0.67f, 1.0f, //
    -0.5f, 0.5f,  -0.5f, 0.33f, 1.0f, //
    -0.5f, -0.5f, -0.5f, 0.33f, 0.0f, //
};
const std::vector<float> Voxel::m_front_face = {
    -0.5f, -0.5f, 0.5f, 0.33f, 0.0f, // Front
    0.5f,  -0.5f, 0.5f, .67f,  0.0f, //
    0.5f,  0.5f,  0.5f, 0.67f, 1.0f, //
    0.5f,  0.5f,  0.5f, 0.67f, 1.0f, //
    -0.5f, 0.5f,  0.5f, 0.33f, 1.0f, //
    -0.5f, -0.5f, 0.5f, 0.33f, 0.0f, //
};
const std::vector<float> Voxel::m_top_face = {
    -0.5f, 0.5f, -0.5f, 0.0f,  1.0f, // Top
    0.5f,  0.5f, -0.5f, 0.33f, 1.0f, //
    0.5f,  0.5f, 0.5f,  0.33f, 0.0f, //
    0.5f,  0.5f, 0.5f,  0.33f, 0.0f, //
    -0.5f, 0.5f, 0.5f,  0.0f,  0.0f, //
    -0.5f, 0.5f, -0.5f, 0.0f,  1.0f  //
};
const std::vector<float> Voxel::m_bottom_face = {
    -0.5f, -0.5f, -0.5f, 0.67f, 0.0f, // Bottom
    0.5f,  -0.5f, -0.5f, 1.0f,  0.0f, //
    0.5f,  -0.5f, 0.5f,  1.0f,  1.0f, //
    0.5f,  -0.5f, 0.5f,  1.0f,  1.0f, //
    -0.5f, -0.5f, 0.5f,  0.67f, 1.0f, //
    -0.5f, -0.5f, -0.5f, 0.67f, 0.0f, //
};
const std::vector<float> Voxel::m_left_face = {
    -0.5f, 0.5f,  0.5f,  0.67f, 1.0f, // Left
    -0.5f, 0.5f,  -0.5f, 0.33f, 1.0f, //
    -0.5f, -0.5f, -0.5f, 0.33f, 0.0f, //
    -0.5f, -0.5f, -0.5f, 0.33f, 0.0f, //
    -0.5f, -0.5f, 0.5f,  0.67f, 0.0f, //
    -0.5f, 0.5f,  0.5f,  0.67f, 1.0f, //
};
const std::vector<float> Voxel::m_right_face = {
    0.5f, 0.5f,  0.5f,  0.33f, 1.0f, // Right
    0.5f, 0.5f,  -0.5f, 0.67f, 1.0f, //
    0.5f, -0.5f, -0.5f, 0.67f, 0.0f, //
    0.5f, -0.5f, -0.5f, 0.67f, 0.0f, //
    0.5f, -0.5f, 0.5f,  0.33f, 0.0f, //
    0.5f, 0.5f,  0.5f,  0.33f, 1.0f, //
};

std::vector<float> Voxel::getVertices(bool front, bool rear, bool top,
                                      bool bottom, bool left, bool right) {
  m_vertices = {};
  if (front)
    m_vertices.insert(m_vertices.end(), m_front_face.begin(),
                      m_front_face.end());
  if (rear)
    m_vertices.insert(m_vertices.end(), m_rear_face.begin(), m_rear_face.end());
  if (top)
    m_vertices.insert(m_vertices.end(), m_top_face.begin(), m_top_face.end());
  if (bottom)
    m_vertices.insert(m_vertices.end(), m_bottom_face.begin(),
                      m_bottom_face.end());
  if (left)
    m_vertices.insert(m_vertices.end(), m_left_face.begin(), m_left_face.end());
  if (right)
    m_vertices.insert(m_vertices.end(), m_right_face.begin(),
                      m_right_face.end());
  return m_vertices;
}

#include <vector>

class Voxel {
  static const std::vector<float> m_rear_face;
  static const std::vector<float> m_front_face;
  static const std::vector<float> m_top_face;
  static const std::vector<float> m_bottom_face;
  static const std::vector<float> m_left_face;
  static const std::vector<float> m_right_face;

  std::vector<float> m_vertices;

public:
  std::vector<float> getVertices(bool front, bool rear, bool top, bool bottom, bool left,
                     bool right);
};

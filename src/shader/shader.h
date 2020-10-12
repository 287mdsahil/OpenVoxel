#pragma once
#include "../vendor/glm/glm.hpp"
#include <string>
#include <unordered_map>

class Shader {
private:
  unsigned int id;
  std::string vertex_shader_filepath;
  std::string fragment_shader_filepath;
  std::string vertex_shader_source;
  std::string fragment_shader_source;
  std::unordered_map<std::string, int> uniform_locations_cache;

  int get_uniform_location(std::string name);
  void parse_shader();
  unsigned int compile_shader(unsigned int type);
  void create_shader();

public:
  Shader(std::string vertex_shader_filepath, std::string index_shader_filepath);
  ~Shader();

  void bind() const;
  void unbind() const;
  void SetUniform1f(const std::string name, float v0);
  void SetUniform1i(const std::string name, int v0);
  void SetUniformMat4f(const std::string name, glm::mat4 &matrix);
  void SetUniform4f(const std::string name, float v0, float v1, float v2,
                    float v3);

};

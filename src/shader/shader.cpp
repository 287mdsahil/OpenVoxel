#include "shader.h"
#include "../error_handling/errorHandling.h"
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <fstream>
#include <iostream>
#include <sstream>

Shader::Shader(std::string vs_filepath, std::string fs_filepath)
    : m_vertex_shader_filepath(vs_filepath),
      m_fragment_shader_filepath(fs_filepath), id(0) {
  parse_shader();
  create_shader();
}

Shader::~Shader() { GlCall(glDeleteProgram(this->id)); }

void Shader::bind() const { GlCall(glUseProgram(id)); }

void Shader::unbind() const { GlCall(glUseProgram(0)); }

void Shader::parse_shader() {

  {
    std::stringstream source;
    std::ifstream source_file(m_vertex_shader_filepath);
    // Vertex shader
    if (source_file) {
      source << source_file.rdbuf();
    } else {
      std::cout << "Unable to read vertex shader file" << std::endl;
    }
    m_vertex_shader_source = source.str();
  }

  {
    std::stringstream source;
    std::ifstream source_file(m_fragment_shader_filepath);
    // Fragment shader
    if (source_file) {
      source << source_file.rdbuf();
    } else {
      std::cout << "Unable to read vertex shader file" << std::endl;
    }
    m_fragment_shader_source = source.str();
  }
}

unsigned int Shader::compile_shader(GLenum type) {
  unsigned int s_id = glCreateShader(type);
  const char *src;
  if (type == GL_VERTEX_SHADER)
    src = m_vertex_shader_source.c_str();
  else if (type == GL_FRAGMENT_SHADER)
    src = m_fragment_shader_source.c_str();

  GlCall(glShaderSource(s_id, 1, &src, nullptr));
  GlCall(glCompileShader(s_id));

  int result;
  GlCall(glGetShaderiv(s_id, GL_COMPILE_STATUS, &result));
  if (result == GLFW_FALSE) {
    int length;
    GlCall(glGetShaderiv(s_id, GL_INFO_LOG_LENGTH, &length));
    char *message = (char *)alloca(length * sizeof(char));
    GlCall(glGetShaderInfoLog(s_id, length, &length, message));
    std::cout << "Failed to compile"
              << ((type == GL_VERTEX_SHADER) ? "vertex" : "fragment")
              << " shader" << std::endl;
    std::cout << message << std::endl;
    GlCall(glDeleteShader(s_id));
    return 0;
  }

  return s_id;
}

void Shader::create_shader() {
  GlCall(unsigned int program = glCreateProgram());
  unsigned int vs = compile_shader(GL_VERTEX_SHADER);
  unsigned int fs = compile_shader(GL_FRAGMENT_SHADER);
  GlCall(glAttachShader(program, vs));
  GlCall(glAttachShader(program, fs));
  GlCall(glLinkProgram(program));
  GlCall(glDeleteShader(vs));
  GlCall(glDeleteShader(fs));
  this->id = program;
}

int Shader::get_uniform_location(const std::string name) {
  int location;
  if (m_uniform_locations_cache.find(name) != m_uniform_locations_cache.end())
    return m_uniform_locations_cache[name];
  GlCall(location = glGetUniformLocation(id, name.c_str()));
  m_uniform_locations_cache[name] = location;
  if (location == -1) {
    std::cout << "Warning: uniform " << name << " doesn't exist!" << std::endl;
  }
  return location;
}

void Shader::SetUniform4f(const std::string name, float v0, float v1, float v2,
                          float v3) {
  GlCall(glUniform4f(get_uniform_location(name), v0, v1, v2, v3));
};

void Shader::SetUniform1f(const std::string name, float v0) {
  GlCall(glUniform1f(get_uniform_location(name), v0));
};

void Shader::SetUniform1i(const std::string name, int v0) {
  GlCall(glUniform1i(get_uniform_location(name), v0));
};

void Shader::SetUniformMat4f(const std::string name, glm::mat4 &matrix) {
  GlCall(glUniformMatrix4fv(get_uniform_location(name), 1, GL_FALSE,
                            &matrix[0][0]));
};

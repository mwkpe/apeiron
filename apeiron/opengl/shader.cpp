#include "shader.h"


#include <fstream>
#include <sstream>
#include <glad/glad.h>
#include "apeiron/engine/error.h"


namespace {


std::string read_file(std::string_view file)
{
  if (std::ifstream fs{std::string{file}}; fs.is_open()) {
    std::stringstream ss;
    ss << fs.rdbuf();
    return ss.str();
  }
  else {
    throw apeiron::engine::Error{std::string{"Could not open shader file: "} + std::string{file}};
  }
}


GLuint create_shader(GLenum type, const std::string& source)
{
  auto id = glCreateShader(type);
  const char* src = source.c_str();
  glShaderSource(id, 1, &src, nullptr);
  glCompileShader(id);
  int success;
  glGetShaderiv(id, GL_COMPILE_STATUS, &success);
  if (!success) {
    char log[512];
    glGetShaderInfoLog(id, 512, nullptr, log);
    throw apeiron::engine::Error{log};
  }
  return id;
}


GLuint create_program(GLuint vertex_shader, GLuint fragment_shader)
{
  auto id = glCreateProgram();
  glAttachShader(id, vertex_shader);
  glAttachShader(id, fragment_shader);
  glLinkProgram(id);
  int success;
  glGetProgramiv(id, GL_LINK_STATUS, &success);
  if (!success) {
    char log[512];
    glGetProgramInfoLog(id, 512, nullptr, log);
    throw apeiron::engine::Error{log};
  }
  glDeleteShader(vertex_shader);
  glDeleteShader(fragment_shader);
  return id;
}


}  // namespace


void apeiron::opengl::Shader::load(std::string_view vertex_shader_file,
    std::string_view fragment_shader_file)
{
  auto vs_source = read_file(vertex_shader_file);
  auto fs_source = read_file(fragment_shader_file);
  auto vertex_shader = create_shader(GL_VERTEX_SHADER, vs_source);
  auto fragment_shader = create_shader(GL_FRAGMENT_SHADER, fs_source);
  id_ = create_program(vertex_shader, fragment_shader);
}


void apeiron::opengl::Shader::compose(const std::vector<std::string>& vertex_shader_files,
      const std::vector<std::string>& fragment_shader_files)
{
  std::string vs_source;
  for (const auto& file : vertex_shader_files) {
    vs_source += read_file(file);
  }

  std::string fs_source;
  for (const auto& file : fragment_shader_files) {
    fs_source += read_file(file);
  }

  auto vertex_shader = create_shader(GL_VERTEX_SHADER, vs_source);
  auto fragment_shader = create_shader(GL_FRAGMENT_SHADER, fs_source);
  id_ = create_program(vertex_shader, fragment_shader);
}


void apeiron::opengl::Shader::use() const
{
  glUseProgram(id_);
}


void apeiron::opengl::Shader::set_uniform(const char* name, bool value) const
{
  glUniform1i(glGetUniformLocation(id_, name), static_cast<int>(value));
}


void apeiron::opengl::Shader::set_uniform(const char* name, std::int32_t value) const
{
  glUniform1i(glGetUniformLocation(id_, name), value);
}


void apeiron::opengl::Shader::set_uniform(const char* name, std::uint32_t value) const
{
  glUniform1ui(glGetUniformLocation(id_, name), value);
}


void apeiron::opengl::Shader::set_uniform(const char* name, float value) const
{
  glUniform1f(glGetUniformLocation(id_, name), value);
}


void apeiron::opengl::Shader::set_uniform(const char* name, const glm::vec2& vec) const
{
  glUniform2fv(glGetUniformLocation(id_, name), 1, &vec[0]);
}


void apeiron::opengl::Shader::set_uniform(const char* name, const glm::vec3& vec) const
{
  glUniform3fv(glGetUniformLocation(id_, name), 1, &vec[0]);
}


void apeiron::opengl::Shader::set_uniform(const char* name, const glm::vec4& vec) const
{
  glUniform4fv(glGetUniformLocation(id_, name), 1, &vec[0]);
}


void apeiron::opengl::Shader::set_uniform(const char* name, const glm::mat4& mat) const
{
  glUniformMatrix4fv(glGetUniformLocation(id_, name), 1, GL_FALSE, &mat[0][0]);
}
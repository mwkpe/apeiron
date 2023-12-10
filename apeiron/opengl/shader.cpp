#include "shader.h"


#include <fstream>
#include <sstream>
#include <glad/glad.h>
#include "apeiron/engine/error.h"


namespace {


std::string read_file(std::string_view file_path)
{
  if (std::ifstream fs{std::string{file_path}}; fs.is_open()) {
    std::stringstream ss;
    ss << fs.rdbuf();
    return ss.str();
  }
  else {
    throw apeiron::engine::Error{"Could not open shader file", file_path};
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


GLuint create_program(GLuint vertex_shader, GLuint fragment_shader, GLuint geometry_shader = 0)
{
  auto id = glCreateProgram();
  glAttachShader(id, vertex_shader);
  glAttachShader(id, fragment_shader);
  if (geometry_shader > 0)
    glAttachShader(id, geometry_shader);
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


void apeiron::opengl::Shader::load(std::string_view vs_file_path, std::string_view fs_file_path,
    std::string_view gs_file_path)
{
  auto vs_source = read_file(vs_file_path);
  auto fs_source = read_file(fs_file_path);
  auto vertex_shader = create_shader(GL_VERTEX_SHADER, vs_source);
  auto fragment_shader = create_shader(GL_FRAGMENT_SHADER, fs_source);

  if (gs_file_path.empty()) {
    id_ = create_program(vertex_shader, fragment_shader);
  }
  else {
    auto gs_source = read_file(gs_file_path);
    auto geometry_shader = create_shader(GL_GEOMETRY_SHADER, gs_source);

    id_ = create_program(vertex_shader, fragment_shader, geometry_shader);
  }
}


void apeiron::opengl::Shader::compose(const std::vector<std::string>& vs_files,
      const std::vector<std::string>& fs_files, const std::vector<std::string>& gs_files)
{
  std::string vs_source;
  for (const auto& file : vs_files) {
    vs_source += read_file(file);
  }

  std::string fs_source;
  for (const auto& file : fs_files) {
    fs_source += read_file(file);
  }

  auto vertex_shader = create_shader(GL_VERTEX_SHADER, vs_source);
  auto fragment_shader = create_shader(GL_FRAGMENT_SHADER, fs_source);

  if (gs_files.empty()) {
    id_ = create_program(vertex_shader, fragment_shader);
  }
  else {
    std::string gs_source;
    for (const auto& file : gs_files) {
      gs_source += read_file(file);
    }

    auto geometry_shader = create_shader(GL_GEOMETRY_SHADER, gs_source);
    id_ = create_program(vertex_shader, fragment_shader, geometry_shader);
  }
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

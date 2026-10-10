#include "shader.h"


#include <array>
#include <fstream>
#include <optional>
#include <sstream>
#include <utility>

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
    throw apeiron::engine::Error::format("Could not open shader file: {}", file_path);
  }
}


class Shader_object final
{
public:
  Shader_object(GLenum type, const std::string& source);
  ~Shader_object() { glDeleteShader(id_); }
  Shader_object(const Shader_object&) = delete;
  Shader_object(Shader_object&&) = delete;
  Shader_object& operator=(const Shader_object&) = delete;
  Shader_object& operator=(Shader_object&&) = delete;

  [[nodiscard]] GLuint id() const { return id_; }

private:
  GLuint id_ = 0;
};


Shader_object::Shader_object(GLenum type, const std::string& source)
{
  const char* src = source.c_str();
  id_ = glCreateShader(type);
  glShaderSource(id_, 1, &src, nullptr);
  glCompileShader(id_);

  int success;
  glGetShaderiv(id_, GL_COMPILE_STATUS, &success);

  if (!success) {
    std::array<char, 512> log{};
    glGetShaderInfoLog(id_, static_cast<GLsizei>(log.size()), nullptr, log.data());
    glDeleteShader(id_);
    throw apeiron::engine::Error{log.data()};
  }
}


GLuint create_program(const std::string& vs_source, const std::string& fs_source,
    const std::string& gs_source)
{
  Shader_object vertex_shader{GL_VERTEX_SHADER, vs_source};
  Shader_object fragment_shader{GL_FRAGMENT_SHADER, fs_source};
  std::optional<Shader_object> geometry_shader;

  if (!gs_source.empty()) {
    geometry_shader.emplace(GL_GEOMETRY_SHADER, gs_source);
  }

  auto id = glCreateProgram();
  glAttachShader(id, vertex_shader.id());
  glAttachShader(id, fragment_shader.id());

  if (geometry_shader) {
    glAttachShader(id, geometry_shader->id());
  }

  glLinkProgram(id);

  int success;
  glGetProgramiv(id, GL_LINK_STATUS, &success);

  if (!success) {
    std::array<char, 512> log{};
    glGetProgramInfoLog(id, static_cast<GLsizei>(log.size()), nullptr, log.data());
    glDeleteProgram(id);
    throw apeiron::engine::Error{log.data()};
  }

  glDetachShader(id, vertex_shader.id());
  glDetachShader(id, fragment_shader.id());

  if (geometry_shader) {
    glDetachShader(id, geometry_shader->id());
  }

  return id;
}


std::string concat_files(const std::vector<std::string>& files)
{
  std::string source;
  for (const auto& file : files) {
    source += read_file(file);
  }

  return source;
}


}  // namespace


apeiron::opengl::Shader::Shader(Shader&& other) noexcept
{
  id_ = std::exchange(other.id_, 0);
}


auto apeiron::opengl::Shader::operator=(Shader&& other) noexcept -> Shader&
{
  if (&other == this) {
    return *this;
  }

  delete_program();
  id_ = std::exchange(other.id_, 0);

  return *this;
}


apeiron::opengl::Shader::~Shader()
{
  delete_program();
}


void apeiron::opengl::Shader::delete_program()
{
  if (id_ > 0) {
    glDeleteProgram(id_);
  }

  id_ = 0;
}


void apeiron::opengl::Shader::load(std::string_view vs_file_path, std::string_view fs_file_path,
    std::string_view gs_file_path)
{
  auto vs_source = read_file(vs_file_path);
  auto fs_source = read_file(fs_file_path);
  auto gs_source = gs_file_path.empty() ? std::string{} : read_file(gs_file_path);

  // Build the new program first so a failed reload keeps the current one
  auto id = create_program(vs_source, fs_source, gs_source);
  delete_program();
  id_ = id;
}


void apeiron::opengl::Shader::compose(const std::vector<std::string>& vs_files,
    const std::vector<std::string>& fs_files, const std::vector<std::string>& gs_files)
{
  auto id = create_program(concat_files(vs_files), concat_files(fs_files), concat_files(gs_files));
  delete_program();
  id_ = id;
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


void apeiron::opengl::Shader::set_uniform(const char* name, const glm::ivec2& vec) const
{
  glUniform2iv(glGetUniformLocation(id_, name), 1, &vec[0]);
}


void apeiron::opengl::Shader::set_uniform(const char* name, const glm::ivec3& vec) const
{
  glUniform3iv(glGetUniformLocation(id_, name), 1, &vec[0]);
}


void apeiron::opengl::Shader::set_uniform(const char* name, const glm::ivec4& vec) const
{
  glUniform4iv(glGetUniformLocation(id_, name), 1, &vec[0]);
}


void apeiron::opengl::Shader::set_uniform(const char* name, const glm::uvec2& vec) const
{
  glUniform2uiv(glGetUniformLocation(id_, name), 1, &vec[0]);
}


void apeiron::opengl::Shader::set_uniform(const char* name, const glm::uvec3& vec) const
{
  glUniform3uiv(glGetUniformLocation(id_, name), 1, &vec[0]);
}


void apeiron::opengl::Shader::set_uniform(const char* name, const glm::uvec4& vec) const
{
  glUniform4uiv(glGetUniformLocation(id_, name), 1, &vec[0]);
}


void apeiron::opengl::Shader::set_uniform(const char* name, const glm::mat4& mat) const
{
  glUniformMatrix4fv(glGetUniformLocation(id_, name), 1, GL_FALSE, &mat[0][0]);
}

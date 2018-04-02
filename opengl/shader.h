#ifndef APEIRON_OPENGL_SHADER_H
#define APEIRON_OPENGL_SHADER_H


#include <cstdint>
#include <string_view>
#include <glm/glm.hpp>


namespace apeiron::opengl {


class Shader final
{
public:
  void load(std::string_view vertex_shader_file, std::string_view fragment_shader_file);
  void use() const;
  void set_uniform(const char* name, bool value) const;
  void set_uniform(const char* name, int value) const;
  void set_uniform(const char* name, const glm::vec3& vec) const;
  void set_uniform(const char* name, const glm::vec4& vec) const;
  void set_uniform(const char* name, const glm::mat4& mat) const;

private:
  std::uint32_t id_ = -1;
};


}  // namespace apeiron::opengl


#endif  // APEIRON_OPENGL_SHADER_H

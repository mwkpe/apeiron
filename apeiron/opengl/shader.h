#ifndef APEIRON_OPENGL_SHADER_H
#define APEIRON_OPENGL_SHADER_H


#include <cstdint>
#include <vector>
#include <string_view>
#include <glm/glm.hpp>


namespace apeiron::opengl {


class Shader final
{
public:
  void load(std::string_view vertex_shader_file, std::string_view fragment_shader_file);
  void compose(const std::vector<std::string>& vertex_shader_files,
      const std::vector<std::string>& fragment_shader_files);
  void use() const;
  void set_uniform(const char* name, bool value) const;
  void set_uniform(const char* name, std::int32_t value) const;
  void set_uniform(const char* name, std::uint32_t value) const;
  void set_uniform(const char* name, float value) const;
  void set_uniform(const char* name, const glm::vec2& vec) const;
  void set_uniform(const char* name, const glm::vec3& vec) const;
  void set_uniform(const char* name, const glm::vec4& vec) const;
  void set_uniform(const char* name, const glm::mat4& mat) const;

private:
  std::uint32_t id_ = 0;
};


}  // namespace apeiron::opengl


#endif  // APEIRON_OPENGL_SHADER_H

#ifndef APEIRON_SHADER_H
#define APEIRON_SHADER_H


#include <cstdint>
#include <string_view>
#include <glm/glm.hpp>


namespace apeiron {


class Shader final
{
public:
  void load(std::string_view vertex_shader_file, std::string_view fragment_shader_file);
  void use() const;
  void set_uniform(const char* name, float x, float y, float z, float w) const;
  void set_uniform(const char* name, const glm::mat4& mat) const;

private:
  std::uint32_t id_ = -1;
};


}  // namespace apeiron


#endif  // APEIRON_SHADER_H

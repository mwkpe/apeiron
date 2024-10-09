#ifndef APEIRON_OPENGL_SHADER_STORAGE_BUFFER_H
#define APEIRON_OPENGL_SHADER_STORAGE_BUFFER_H


#include <cstdint>
#include <vector>
#include <glad/glad.h>
#include "apeiron/engine/error.h"


namespace apeiron::opengl {


class Shader_storage_buffer
{
public:
  Shader_storage_buffer() = default;
  ~Shader_storage_buffer();
  Shader_storage_buffer(const Shader_storage_buffer&) = delete;
  Shader_storage_buffer(Shader_storage_buffer&&) noexcept;
  Shader_storage_buffer& operator=(const Shader_storage_buffer&) = delete;
  Shader_storage_buffer& operator=(Shader_storage_buffer&&) noexcept;

  template<typename T> void init(std::uint32_t binding_point, const std::vector<T>& data);
  template<typename T> void update(const std::vector<T>& data);

  void bind() const;
  void unbind() const;

private:
  void delete_buffer();

  const std::uint32_t invalid_binding_point_ = 0xffff'ffff;

  std::uint32_t id_ = 0;
  std::uint32_t binding_point_ = invalid_binding_point_;
  std::uint32_t binding_point_hardware_limit_ = 0;
};


template<typename T> void Shader_storage_buffer::init(std::uint32_t binding_point,
    const std::vector<T>& data)
{
  delete_buffer();

  std::int32_t limit = 0;
  glGetIntegerv(GL_MAX_SHADER_STORAGE_BUFFER_BINDINGS, &limit);
  binding_point_hardware_limit_ = static_cast<std::uint32_t>(limit);

  if (binding_point >= binding_point_hardware_limit_) {
    throw engine::Error{"Shader storage buffer binding point exceeds hardware limit"};
  }

  glGenBuffers(1, &id_);

  if (id_ == 0) {
    throw engine::Error{"Error creating shader storage buffer"};
  }

  binding_point_ = binding_point;

  glBindBufferBase(GL_SHADER_STORAGE_BUFFER, binding_point_, id_);
  glBufferData(GL_SHADER_STORAGE_BUFFER, data.size() * sizeof(T), data.data(), GL_STATIC_DRAW);
}


template<typename T> void Shader_storage_buffer::update(const std::vector<T>& data)
{
  if (id_ == 0 || binding_point_ == invalid_binding_point_) {
    return;
  }

  glBindBufferBase(GL_SHADER_STORAGE_BUFFER, binding_point_, id_);
  glBufferSubData(GL_SHADER_STORAGE_BUFFER, 0, data.size() * sizeof(T), data.data());
}


}  // namespace apeiron::opengl


#endif  // APEIRON_OPENGL_SHADER_STORAGE_BUFFER_H

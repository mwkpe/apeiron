#ifndef APEIRON_OPENGL_VERTEX_ARRAY_H
#define APEIRON_OPENGL_VERTEX_ARRAY_H


#include <cstdint>
#include <vector>
#include "apeiron/engine/vertex.h"
#include "apeiron/opengl/enums.h"


namespace apeiron::opengl {


class Vertex_array
{
public:
  Vertex_array();
  virtual ~Vertex_array();
  Vertex_array(const Vertex_array&) = delete;
  Vertex_array(Vertex_array&& other) noexcept;
  Vertex_array& operator=(const Vertex_array&) = delete;
  Vertex_array& operator=(Vertex_array&& other) noexcept;

  virtual void render() const {};
  virtual void render([[maybe_unused]] std::uint32_t index) const {};
  virtual void render([[maybe_unused]] std::uint32_t start,
      [[maybe_unused]] std::uint32_t count) const {}

protected:
  void delete_buffers();
  template<typename T> void set_buffers(const std::vector<T>& vertices,
      Usage_hint hint = Usage_hint::Static);
  template<typename T> void update_buffers(const std::vector<T>& vertices);

  std::uint32_t vao_ = 0;
  std::uint32_t vbo_ = 0;
  std::uint32_t vertex_size_ = 0;
  std::uint32_t vertex_count_ = 0;

private:
  std::uint32_t usage_hint_ = 0;
};


}  // namespace apeiron::opengl


#endif  // APEIRON_OPENGL_VERTEX_ARRAY_H

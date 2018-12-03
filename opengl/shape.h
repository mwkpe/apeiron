#ifndef APEIRON_OPENGL_SHAPE_H
#define APEIRON_OPENGL_SHAPE_H


#include <cstdint>
#include <vector>
#include "engine/vertex.h"


namespace apeiron::opengl {


class Shape
{
public:
  Shape() = default;
  virtual ~Shape();
  Shape(const Shape&) = delete;
  Shape(Shape&& other) noexcept;
  Shape& operator=(const Shape&) = delete;
  Shape& operator=(Shape&& other) noexcept;

  virtual void render() const {};
  virtual void render([[maybe_unused]] std::uint32_t start,
      [[maybe_unused]] std::uint32_t count) const {}

protected:
  void delete_buffers();
  template<typename T> void set_buffers(const std::vector<T>& vertices);

  std::uint32_t vao_ = 0;
  std::uint32_t vbo_ = 0;
  std::uint32_t ebo_ = 0;
  std::uint32_t vertex_count_ = 0;
  std::uint32_t element_count_ = 0;
};


}  // namespace apeiron::opengl


#endif  // APEIRON_OPENGL_SHAPE_H

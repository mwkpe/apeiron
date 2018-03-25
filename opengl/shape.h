#ifndef APEIRON_OPENGL_SHAPE_H
#define APEIRON_OPENGL_SHAPE_H


#include <cstdint>


namespace apeiron::opengl {


class Shape
{
public:
  Shape() = default;
  virtual ~Shape();
  // OpenGL delete calls in destructor
  Shape(const Shape&) = delete;
  Shape(Shape&&) = delete;
  Shape& operator=(const Shape&) = delete;
  Shape& operator=(Shape&&) = delete;

  virtual void render() const = 0;

protected:
  std::uint32_t vao_ = 0;
  std::uint32_t vbo_ = 0;
  std::uint32_t vertex_count_ = 0;
};


}  // namespace apeiron::opengl



#endif  // APEIRON_OPENGL_SHAPE_H

#ifndef APEIRON_PRIMITIVES_H
#define APEIRON_PRIMITIVES_H


#include <cstdint>


namespace apeiron::primitives {


class Cube final
{
public:
  Cube();
  ~Cube();
  // OpenGL delete calls in destructor
  Cube(const Cube&) = delete;
  Cube(Cube&&) = delete;
  Cube& operator=(const Cube&) = delete;
  Cube& operator=(Cube&&) = delete;

  void render() const;

private:
  std::uint32_t vao_ = 0;
  std::uint32_t vbo_ = 0;
  std::uint32_t vertex_count_ = 0;
};


class Cylinder final
{
public:
  Cylinder(int points);
  ~Cylinder();
  // OpenGL delete calls in destructor
  Cylinder(const Cylinder&) = delete;
  Cylinder(Cylinder&&) = delete;
  Cylinder& operator=(const Cylinder&) = delete;
  Cylinder& operator=(Cylinder&&) = delete;

  void construct(int points);
  void render() const;
  int points() const { return points_; }

private:
  std::uint32_t vao_ = 0;
  std::uint32_t vbo_ = 0;
  std::uint32_t vertex_count_ = 0;
  int points_;
};


}  // namespace apeiron::primitives


#endif  // APEIRON_PRIMITIVES_H

#ifndef APEIRON_PRIMITIVES_H
#define APEIRON_PRIMITIVES_H


#include <cstdint>


namespace apeiron::primitives {


class Cube
{
public:
  Cube();
  void render() const;

private:
  std::uint32_t vao_;
  std::uint32_t vbo_;
  std::uint32_t vertex_count_;
};


class Cylinder
{
public:
  Cylinder(int points);
  void render() const;

private:
  std::uint32_t vao_;
  std::uint32_t vbo_;
  std::uint32_t vertex_count_;
};


}  // namespace apeiron::primitives


#endif  // APEIRON_PRIMITIVES_H

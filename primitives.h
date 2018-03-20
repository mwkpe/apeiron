#ifndef APEIRON_PRIMITIVES_H
#define APEIRON_PRIMITIVES_H


#include <cstdint>


namespace apeiron::primitives {


class Cube
{
public:
  Cube();
  ~Cube();
  void render() const;

private:
  std::uint32_t vao_ = 0;
  std::uint32_t vbo_ = 0;
  std::uint32_t vertex_count_ = 0;
};


class Cylinder
{
public:
  Cylinder(int points);
  ~Cylinder();
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

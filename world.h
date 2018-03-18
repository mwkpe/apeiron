#ifndef APEIRON_WORLD_H
#define APEIRON_WORLD_H


#include <cstdint>
#include "shader.h"
#include "primitives.h"


namespace apeiron {


class World
{
public:
  World() : cylinder_{8} {}
  void init();
  void render(float time);

private:
  Shader shader_;
  primitives::Cylinder cylinder_;
  primitives::Cube cube_;
};


}  // namespace apeiron


#endif  // APEIRON_WORLD_H

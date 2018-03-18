#ifndef APEIRON_WORLD_H
#define APEIRON_WORLD_H


#include <cstdint>
#include "options.h"
#include "shader.h"
#include "primitives.h"


namespace apeiron {


class World
{
public:
  World(const Options& options) : options_{options}, cylinder_{8} {}
  void init();
  void render(float time);

private:
  const Options& options_;
  int frame_ = 0;
  float frame_time_ = 0;
  Shader shader_;
  primitives::Cylinder cylinder_;
  primitives::Cube cube_;
};


}  // namespace apeiron


#endif  // APEIRON_WORLD_H

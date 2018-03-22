#ifndef APEIRON_WORLD_H
#define APEIRON_WORLD_H


#include <cstdint>
#include "options.h"
#include "input.h"
#include "shader.h"
#include "primitives.h"
#include "model.h"
#include "camera.h"


namespace apeiron {


class World final
{
public:
  World(const Options* options) : options_{options}, cylinder_{options_->cylinder_points} {}
  void init();
  void reset();
  void update(float delta_time, const Input* input = nullptr);
  void render(float time);

private:
  const Options* options_;
  int frame_ = 0;
  float frame_time_ = 0;
  Shader shader_;
  Camera camera_;
  primitives::Cylinder cylinder_;
  primitives::Cube cube_;
  Model car_;
};


}  // namespace apeiron


#endif  // APEIRON_WORLD_H

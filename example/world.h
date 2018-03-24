#ifndef APEIRON_EXAMPLE_WORLD_H
#define APEIRON_EXAMPLE_WORLD_H


#include <cstdint>
#include "options.h"
#include "engine/input.h"
#include "engine/camera.h"
#include "opengl/renderer.h"
#include "example/vehicle.h"


namespace apeiron::example {


class World final
{
public:
  World(const Options* options) : options_{options} {}
  void init();
  void reset();
  void update(float delta_time, const engine::Input* input = nullptr);
  void render(float time);

private:
  const Options* options_;
  opengl::Renderer renderer_;
  engine::Camera camera_;
  Vehicle car_;
  Vehicle pirate_ship_;
  int frame_ = 0;
  float frame_time_ = 0;
};


}  // namespace apeiron::example


#endif  // APEIRON_EXAMPLE_WORLD_H

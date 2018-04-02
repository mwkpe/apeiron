#ifndef APEIRON_EXAMPLE_WORLD_H
#define APEIRON_EXAMPLE_WORLD_H


#include <cstdint>
#include <vector>
#include "options.h"
#include "engine/input.h"
#include "opengl/texture.h"
#include "opengl/model.h"
#include "engine/camera.h"
#include "opengl/cube.h"
#include "opengl/renderer.h"
#include "example/ground.h"
#include "example/light.h"
#include "example/vehicle.h"
#include "example/cylinder.h"
#include "example/poneglyph.h"


namespace apeiron::example {


class World final
{
public:
  World(const Options* options) : options_{options},
      ground_{{30.0f, 0.0f, 200.0f}, {2.5f, 0.0f, 2.5f}, 0.01f},
      light_{&bulb_},
      cylinder_{options_->cylinder_points, 0.0f, 0.0f, 1.0f} {}

  void init();
  void reset();
  void update(float time, float delta_time, const engine::Input* input = nullptr);
  void render();

private:
  const Options* options_;
  opengl::Renderer renderer_;
  opengl::Texture akari_;
  opengl::Model bulb_;
  opengl::Cube cube_;
  engine::Camera camera_;
  Ground ground_;
  Light light_;
  Vehicle car_;
  Vehicle pirate_ship_;
  Cylinder cylinder_;
  std::vector<Poneglyph> poneglyphs_;
  int frame_ = 0;
  float frame_time_ = 0;
};


}  // namespace apeiron::example


#endif  // APEIRON_EXAMPLE_WORLD_H

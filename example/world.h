#ifndef APEIRON_EXAMPLE_WORLD_H
#define APEIRON_EXAMPLE_WORLD_H


#include <cstdint>
#include <vector>
#include "options.h"
#include "engine/input.h"
#include "opengl/texture.h"
#include "opengl/model.h"
#include "engine/camera.h"
#include "engine/text.h"
#include "opengl/cuboid.h"
#include "opengl/renderer.h"
#include "example/ground.h"
#include "example/light.h"
#include "example/cube.h"
#include "example/cylinder.h"
#include "example/teapot.h"


namespace apeiron::example {


class World final
{
public:
  explicit World(const Options* options) : options_{options},
      charset_{16, 8, 32},
      cube_{{1.0f, 1.0f, 1.0f}},
      ground_{{50.0f, 50.0f}, 20, 20, {0.25f, 0.25f, 0.25f}, 1.0f},
      light_{&bulb_},
      cylinder_{options_->cylinder_points, 0.0f, 0.0f, 1.0f} {}
  void init();
  void update(float time, float delta_time, const engine::Input* input = nullptr);
  void render();

private:
  const Options* options_;
  opengl::Renderer renderer_;
  opengl::Charset charset_;
  opengl::Texture akari_;
  opengl::Model bulb_;
  opengl::Cuboid cube_;
  engine::Camera camera_;
  engine::Text text_;
  Ground ground_;
  Light light_;
  Cylinder cylinder_;
  std::vector<Cube> cubes_;
  Teapot teapot_;
  int frame_ = 0;
  float frame_time_ = 0;
};


}  // namespace apeiron::example


#endif  // APEIRON_EXAMPLE_WORLD_H

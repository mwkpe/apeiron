#ifndef APEIRON_EXAMPLE_WORLD_H
#define APEIRON_EXAMPLE_WORLD_H


#include <cstdint>
#include <vector>
#include "options.h"
#include "opengl/renderer.h"
#include "opengl/texture.h"
#include "opengl/tileset.h"
#include "opengl/cuboid.h"
#include "opengl/model.h"
#include "engine/input.h"
#include "engine/camera.h"
#include "engine/text.h"
#include "prefab/axes.h"
#include "prefab/ground.h"
#include "prefab/light.h"
#include "prefab/teapot.h"
#include "example/cube.h"
#include "example/cylinder.h"


namespace apeiron::example {


class World final
{
public:
  explicit World(const Options* options);
  void init();
  void update(float time, float delta_time, const engine::Input* input = nullptr);
  void render();

private:
  void update_camera(float delta_time, const engine::Input* input);
  void handle_mouse_move(int x, int y);
  void handle_mouse_click(int x, int y);

  const Options* options_;
  opengl::Renderer renderer_;
  opengl::Tileset charset_;
  opengl::Texture cube_texture_;
  opengl::Cuboid cube_model_;
  opengl::Model bulb_;
  engine::Camera camera_;
  engine::Text world_text_;
  engine::Text screen_text_;
  prefab::Axes axes_;
  prefab::Ground ground_;
  prefab::Light light_;
  prefab::Teapot teapot_;
  Cylinder cylinder_;
  std::vector<Cube> cubes_;
  bool mouse_left_down_ = false;
  int frame_ = 0;
  float frame_time_ = 0;
};


}  // namespace apeiron::example


#endif  // APEIRON_EXAMPLE_WORLD_H

#ifndef APEIRON_EXAMPLE_WORLD_H
#define APEIRON_EXAMPLE_WORLD_H


#include <cstdint>
#include <vector>
#include "engine/input.h"
#include "engine/event.h"
#include "engine/camera.h"
#include "engine/text.h"
#include "opengl/renderer.h"
#include "opengl/texture.h"
#include "opengl/tileset.h"
#include "opengl/cuboid.h"
#include "opengl/model.h"
#include "prefab/axes.h"
#include "prefab/ground.h"
#include "prefab/light.h"
#include "prefab/teapot.h"
#include "example/options.h"
#include "example/cube.h"
#include "example/cylinder.h"
#include "example/ground_highlight.h"


namespace apeiron::example {


class World final
{
public:
  explicit World(const Options* options);
  void init();
  void update(float time, float delta_time, const std::vector<apeiron::engine::Event>& events,
      const engine::Input* input = nullptr);
  void render();

  // Event handling
  void operator()(const engine::Mouse_motion_event& event);
  void operator()(const engine::Mouse_button_down_event& event);
  void operator()(const engine::Mouse_button_up_event& event);
  void operator()(const engine::Mouse_wheel_event& event);

private:
  void update_camera(float delta_time, const engine::Input* input);

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
  Ground_highlight ground_highlight_;
  std::vector<Cube> cubes_;
  int frame_ = 0;
  float frame_time_ = 0;
};


}  // namespace apeiron::example


#endif  // APEIRON_EXAMPLE_WORLD_H

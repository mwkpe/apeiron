#ifndef APEIRON_EXAMPLE_WORLD_H
#define APEIRON_EXAMPLE_WORLD_H


#include <cstdint>
#include <vector>
#include "apeiron/engine/input.h"
#include "apeiron/engine/event.h"
#include "apeiron/engine/camera.h"
#include "apeiron/engine/text.h"
#include "apeiron/opengl/renderer.h"
#include "apeiron/opengl/frame_buffer.h"
#include "apeiron/opengl/texture.h"
#include "apeiron/opengl/tileset.h"
#include "apeiron/opengl/mesh_font.h"
#include "apeiron/opengl/cuboid.h"
#include "apeiron/opengl/model.h"
#include "apeiron/prefab/axes.h"
#include "apeiron/prefab/grid.h"
#include "apeiron/prefab/light.h"
#include "apeiron/prefab/teapot.h"
#include "example/settings.h"
#include "example/cube.h"
#include "example/cylinder.h"
#include "example/ground_highlight.h"


namespace apeiron::example {


class World final
{
public:
  explicit World(const Settings* settings);
  void init();
  void update(float time, float delta_time, const apeiron::engine::Event_queue& events,
      const engine::Input* input = nullptr);
  void render();

  // Event handling
  void operator()(const apeiron::engine::Key_down_event& event);
  void operator()(const apeiron::engine::Key_up_event& event);
  void operator()(const apeiron::engine::Mouse_button_down_event& event);
  void operator()(const apeiron::engine::Mouse_button_up_event& event);
  void operator()(const apeiron::engine::Mouse_motion_event& event);
  void operator()(const apeiron::engine::Mouse_wheel_event& event);
  void operator()(const apeiron::engine::Controller_button_down_event& event);
  void operator()(const apeiron::engine::Controller_button_up_event& event);
  void operator()(const apeiron::engine::Controller_axis_motion_event& event);

private:
  void update_camera(float delta_time, const engine::Input* input);

  const Settings* settings_;
  opengl::Renderer renderer_;
  opengl::Tileset bitmap_charset_;
  opengl::Mesh_font mesh_charset_;
  opengl::Texture cube_texture_;
  opengl::Cuboid cube_model_;
  opengl::Model bulb_;
  engine::Camera camera_;
  engine::Text world_text_;
  engine::Text screen_text_;
  prefab::Axes axes_;
  prefab::Grid grid_;
  prefab::Light light_;
  prefab::Teapot teapot_;
  Cylinder cylinder_;
  Ground_highlight ground_highlight_;
  Cube cube_;
  std::vector<Cube> cubes_;
  int frame_ = 0;
  float frame_time_ = 0;
};


}  // namespace apeiron::example


#endif  // APEIRON_EXAMPLE_WORLD_H

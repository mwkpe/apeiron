#ifndef APEIRON_EXAMPLE_WORLD_H
#define APEIRON_EXAMPLE_WORLD_H


#include <vector>

#include "apeiron/engine/camera.h"
#include "apeiron/engine/camera_controller.h"
#include "apeiron/engine/event.h"
#include "apeiron/engine/font.h"
#include "apeiron/engine/input.h"

#include "apeiron/opengl/cuboid.h"
#include "apeiron/opengl/model.h"
#include "apeiron/opengl/renderer.h"
#include "apeiron/opengl/text.h"
#include "apeiron/opengl/texture.h"

#include "apeiron/prefab/xy_axes.h"
#include "apeiron/prefab/grid.h"
#include "apeiron/prefab/light.h"
#include "apeiron/prefab/origin.h"
#include "apeiron/prefab/teapot.h"

#include "example/settings.h"
#include "example/cube.h"
#include "example/ground_highlight.h"


namespace apeiron::example {


class World final
{
public:
  explicit World(const Settings* settings);
  void init();
  void update_view();
  void update(float time, float delta_time, const apeiron::engine::Event_queue& events,
      const engine::Input* input = nullptr);
  void render();

  // Event handling
  template<typename T> void operator()(const T& event)
  {
    if constexpr (requires { this->handle_event(event); }) {
      this->handle_event(event);
    }
  }

private:
  // Event handling
  void handle_event(const apeiron::engine::Mouse_button_down_event& event);
  void handle_event(const apeiron::engine::Mouse_motion_event& event);

  void update_controller(float delta_time, const engine::Input* input);

  const Settings* settings_;
  opengl::Renderer renderer_;
  opengl::Model mesh_charset_;
  opengl::Texture cube_texture_;
  opengl::Cuboid cube_model_;
  opengl::Model bulb_;
  opengl::Text world_text_;
  opengl::Text screen_text_;
  opengl::Multi_text axes_legend_;
  engine::Camera camera_;
  engine::Free_controller free_controller_;
  engine::Font<engine::Vertex_normal> font_;
  prefab::Xy_axes xy_axes_;
  prefab::Origin origin_;
  prefab::Grid grid_;
  prefab::Light light_;
  prefab::Teapot teapot_;
  Ground_highlight ground_highlight_;
  Cube cube_;
  std::vector<Cube> cubes_;
  int frame_ = 0;
  float frame_time_ = 0;
};


}  // namespace apeiron::example


#endif  // APEIRON_EXAMPLE_WORLD_H

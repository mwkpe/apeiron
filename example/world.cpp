#include "world.h"


#include <random>
#include <glm/gtc/matrix_transform.hpp>
#include "engine/model_flags.h"


void apeiron::example::World::init()
{
  namespace mf = engine::model_flags;

  renderer_.init(static_cast<float>(options_->window_width),
      static_cast<float>(options_->window_height));
  camera_.set({10.0f, 15.0f, 10.0f}, -45.0f, -145.0f);

  charset_.load("assets/roboto_mono.png");
  akari_.load("assets/private/checkerboard.png");
  bulb_.load("assets/private/bulb.obj", mf::vertices);
  teapot_.load_model("assets/utah_teapot.obj", mf::vertices | mf::normals);
  light_.set_position(0.0f, 7.5f, -options_->light_distance);
  light_.set_color(1.0f, 1.0f, 1.0f);
  renderer_.set_light_position(light_.position());
  renderer_.set_light_color(light_.color());
  teapot_.set_position(0.0f, 0.0f, 4.13102f / 2.0f + 0.1f);  // Recede to prevent z-fighting
  teapot_.set_center(0.0f, 1.271f / 2.0f, 0.0f);  // Offset model origin to center
  cylinder_.set_position(0.0f, 0.5f, -5.0f);

  std::mt19937 rng{0x102df64d};
  std::uniform_real_distribution<float> dist(0.0f, 50.0f);
  auto rotation = [&rng, &dist](float factor = 1.0f){ return (dist(rng) / 25.0f - 1.0f) * factor; };
  auto position = [&rng, &dist]{ return dist(rng) - 25.0f; };

  for (int i=0; i<50; ++i) {
    switch (i % 3) {
      case 0: cubes_.emplace_back(&cube_, 0.0f, rotation(0.2f), rotation());
        break;
      case 1: cubes_.emplace_back(&cube_, rotation(), 0.0f, rotation(0.2f));
        break;
      case 2: cubes_.emplace_back(&cube_, rotation(0.2f), rotation(), 0.0f);
        break;
      default:;
    }
    cubes_.back().set_position(position(), position(), position());
  }

  world_text_.set_text(" !\"#$%&'()*+,-./0123456789:;<=>?");
  world_text_.set_position(5.0f, 0.1f, 0.0f);
  world_text_.set_rotation(glm::radians(90.0f), 0.0f, 0.0f);
  world_text_.set_size(1.0f);
  world_text_.set_spacing(0.95f, 1.0f);

  screen_text_.set_text(" !\"#$%&'()*+,-./0123456789:;<=>?");
  screen_text_.set_position(100.0f, 100.0f, 0.0f);
  screen_text_.set_size(100.0f);
  screen_text_.set_spacing(0.95f, 1.0f);
}


void apeiron::example::World::update(float time, float delta_time, const engine::Input* input)
{
  if (options_->rotate_cubes)
    frame_time_ = time;

  if (input) {
    using Direction = engine::Camera::Direction;
    auto distance = options_->camera_speed * delta_time;
    if (input->forward)
      camera_.move(Direction::Forward, distance);
    if (input->backward)
      camera_.move(Direction::Backward, distance);
    if (input->left)
      camera_.move(Direction::Left, distance);
    if (input->right)
      camera_.move(Direction::Right, distance);

    camera_.orient(input->mouse_x_rel, input->mouse_y_rel, options_->camera_sensitivity);

    if (input->mouse_left)
      screen_text_.set_text("mouse left");
    if (input->mouse_middle)
      screen_text_.set_text("mouse middle");
    if (input->mouse_right)
      screen_text_.set_text("mouse right");
  }

  if (options_->lighting) {
    const auto& mc = options_->main_color;
    light_.set_color(mc.r, mc.g, mc.b);
  }
  else {
    light_.set_color(0.3f, 0.3f, 0.3f);
  }
  light_.set_position(0.0f, 7.5f, -options_->light_distance);

  cylinder_.set_rotation(frame_time_ * glm::radians(360.0f * options_->cylinder_revs) *
      cylinder_.rotation_magnitudes());
  if (cylinder_.points() != options_->cylinder_points) {
    cylinder_.rebuild(options_->cylinder_points);
  }

  for (auto& c : cubes_) {
    c.set_rotation(frame_time_ * glm::radians(120.0f) * c.rotation_magnitudes());
  }

  world_text_.set_text(options_->text);
  screen_text_.set_text(options_->text);
}


void apeiron::example::World::render()
{
  frame_++;
  auto color = options_->main_color;

  renderer_.use_world_space();
  auto aspect_ratio = static_cast<float>(options_->window_width) / options_->window_height;
  renderer_.set_projection(glm::perspective(glm::radians(45.0f), aspect_ratio, 0.1f, 500.0f));

  renderer_.set_view(camera_.view());
  renderer_.set_wireframe(options_->wireframe);
  renderer_.set_lighting(false);
  renderer_.set_colorize(false);

  renderer_.use_vertex_color_shading();
  renderer_.render(ground_);

  renderer_.use_color_shading();
  renderer_.render(cylinder_, color);

  if (options_->lighting) {
    renderer_.set_light_color(light_.color());
    renderer_.set_light_position(light_.position());
    renderer_.set_lighting(true);
  }
  renderer_.render(teapot_, color);

  renderer_.set_lighting(false);
  renderer_.use_color_shading();
  renderer_.render_bounds(teapot_, color);

  if (options_->show_light) {
    renderer_.set_lighting(false);
    renderer_.render(light_, light_.color());
  }

  if (options_->show_cubes) {
    renderer_.use_texture_shading();
    akari_.bind();
    for (const auto& c : cubes_) {
      renderer_.render(c);
    }
  }

  renderer_.render(world_text_, charset_, color);

  renderer_.use_screen_space();
  renderer_.set_projection(glm::ortho(-1.0f, 1.0f, 1.0f, -1.0f));

  renderer_.render_screen(screen_text_, charset_, color);
}

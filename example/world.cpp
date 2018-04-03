#include "world.h"


#include <random>
#include <glm/gtc/matrix_transform.hpp>
#include "engine/model_flags.h"


void apeiron::example::World::init()
{
  namespace mf = engine::model_flags;

  renderer_.init();
  akari_.load("assets/akari.png");
  bulb_.load("assets/bulb.obj", mf::vertices);
  car_.load_model("assets/bmw.obj", mf::vertices | mf::normals | mf::tex_coords);
  car_.load_texture("assets/bmw.png");
  pirate_ship_.load_model("assets/schooner.obj", mf::vertices | mf::tex_coords);
  pirate_ship_.load_texture("assets/palitra.png");
  light_.set_position(0.0f, 7.5f, -options_->light_distance);
  light_.set_color(1.0f, 1.0f, 1.0f);
  renderer_.set_light_position(light_.position());
  renderer_.set_light_color(light_.color());
  car_.set_position(0.0f, 0.0f, 4.13102f / 2.0f + 0.1f);  // Recede to prevent z-fighting
  car_.set_center(0.0f, 1.271f / 2.0f, 0.0f);  // Offset model origin to center
  cylinder_.set_position(0.0f, 0.5f, -options_->cylinder_distance);

  std::mt19937 rng{0x299df84d};
  std::uniform_real_distribution<float> dist(0.0f, 100.0f);
  auto rotation = [&rng, &dist](float factor = 1.0f){ return (dist(rng) / 50.0f - 1.0f) * factor; };
  auto position = [&rng, &dist]{ return dist(rng) - 50.0f; };

  for (int i=0; i<300; ++i) {
    switch (i % 3) {
      case 0: poneglyphs_.emplace_back(&cube_, 0.0f, rotation(0.2f), rotation());
        break;
      case 1: poneglyphs_.emplace_back(&cube_, rotation(), 0.0f, rotation(0.2f));
        break;
      case 2: poneglyphs_.emplace_back(&cube_, rotation(0.2f), rotation(), 0.0f);
        break;
      default:;
    }
    poneglyphs_.back().set_position(position(), position(), position());
  }
}


void apeiron::example::World::reset()
{
  camera_.reset();
}


void apeiron::example::World::update(float time, float delta_time, const engine::Input* input)
{
  if (options_->autorotate)
    frame_time_ = time;

  if (input) {
    using Direction = engine::Camera::Direction;
    auto distance = options_->velocity * delta_time;
    if (input->forward)
      camera_.move(Direction::Forward, distance);
    if (input->backward)
      camera_.move(Direction::Backward, distance);
    if (input->left)
      camera_.move(Direction::Left, distance);
    if (input->right)
      camera_.move(Direction::Right, distance);

    camera_.orient(input->mouse_x_rel, input->mouse_y_rel, options_->sensitivity);
  }

  if (options_->lighting) {
    const auto& mc = options_->main_color;
    light_.set_color(mc.r, mc.g, mc.b);
  }
  else {
    light_.set_color(0.3f, 0.3f, 0.3f);
  }
  light_.set_position(0.0f, 7.5f, -options_->light_distance);
  renderer_.set_light_color(light_.color());
  renderer_.set_light_position(light_.position());

  cylinder_.set_position(0.0f, 0.5f, -options_->cylinder_distance);
  cylinder_.set_rotation(frame_time_ * glm::radians(360.0f * options_->cylinder_revs) *
      cylinder_.rotation_magnitudes());
  if (cylinder_.points() != options_->cylinder_points) {
    cylinder_.rebuild(options_->cylinder_points);
  }

  for (auto& p : poneglyphs_) {
    p.set_rotation(frame_time_ * glm::radians(120.0f) * p.rotation_magnitudes());
  }
}


void apeiron::example::World::render()
{
  frame_++;
  auto color = options_->main_color;
  auto aspect_ratio = static_cast<float>(options_->window_width) / options_->window_height;

  renderer_.set_projection(glm::perspective(glm::radians(45.0f), aspect_ratio, 1.5f, 500.0f));
  renderer_.set_view(camera_.view());
  renderer_.set_wireframe(options_->wireframe);

  renderer_.use_vertex_color_shading();
  renderer_.render(ground_);

  if (options_->pirate_mode) {
    renderer_.use_texture_shading();
    renderer_.render(pirate_ship_);
    akari_.bind();
    for (const auto& p : poneglyphs_) {
      renderer_.render(p);
    }
  }
  else {
    renderer_.set_lighting(options_->lighting);
    renderer_.use_texture_shading();
    renderer_.render(car_);
    renderer_.set_lighting(false);
    renderer_.use_color_shading();
    renderer_.render_bounds(car_, glm::vec4{0.611f, 0.152f, 0.690f, 1.0f});
  }
  renderer_.use_color_shading();
  renderer_.render(cylinder_, color);

  if (options_->show_light) {
    if (options_->lighting)
      renderer_.set_lighting(false);
    auto lc = light_.color();
    renderer_.render(light_, {lc.r, lc.g, lc.b, 1.0f});
  }
}

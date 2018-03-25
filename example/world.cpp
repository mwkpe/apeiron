#include "world.h"


#include <random>
#include <glm/gtc/matrix_transform.hpp>


void apeiron::example::World::init()
{
  renderer_.init();
  car_.load_model("assets/camaro.obj");
  pirate_ship_.load_model("assets/pirate_ship.obj");

  ground_.set_scale(3.6f, 0.1f, 100.0f);
  ground_.set_position(0.0f, -0.5f, 0.0f);
  cylinder_.set_position(0.0f, 1.0f, -10.0f);

  std::mt19937 rng;
  rng.seed(std::random_device{}());
  std::uniform_int_distribution<std::mt19937::result_type> dist(0, 10000);
  auto rotation = [&rng, &dist]{ return static_cast<float>(dist(rng)) / 5000.0f - 1.0f; };
  auto position = [&rng, &dist]{ return static_cast<float>(dist(rng)) / 100.0f - 50.0f; };

  for (int i=0; i<200; ++i) {
    switch (i % 3) {
      case 0: poneglyphs_.emplace_back(&cube_, 0.0f, rotation(), rotation()); break;
      case 1: poneglyphs_.emplace_back(&cube_, rotation(), 0.0f, rotation()); break;
      case 2: poneglyphs_.emplace_back(&cube_, rotation(), rotation(), 0.0f); break;
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

  cylinder_.set_rotation(frame_time_ * glm::radians(360.0f * options_->cylinder_revs) *
      cylinder_.rotation_magnitudes());
  if (cylinder_.points() != options_->cylinder_points) {
    cylinder_.rebuild(options_->cylinder_points);
  }

  for (auto& p : poneglyphs_) {
    p.set_rotation(frame_time_ * glm::radians(120.0f) * p.rotation_magnitudes());
  }
}


void apeiron::example::World::render(float time)
{
  frame_++;
  auto color = options_->main_color;

  renderer_.set_projection(glm::perspective(glm::radians(45.0f), 1280.0f / 720.0f, 0.1f, 1000.0f));
  renderer_.set_view(camera_.view());

  renderer_.set_wireframe(options_->wireframe);

  if (options_->strobe && (frame_ % 8 < 4))
    renderer_.set_wireframe(true);
  else if (options_->strobe)
    renderer_.set_wireframe(false);

  if (options_->pirate_mode) {
    renderer_.render(pirate_ship_, color);
    for (const auto& p : poneglyphs_) {
      renderer_.render(p, color);
    }
  }
  else {
    renderer_.render(car_, color);
  }

  renderer_.render(cylinder_, color);

  renderer_.set_wireframe(false);
  renderer_.render(ground_, engine::Color{0.2f, 0.2f, 0.2f, 1.0f});
}

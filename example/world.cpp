#include "world.h"


#include <glm/gtc/matrix_transform.hpp>


void apeiron::example::World::init()
{
  renderer_.init();
  car_.load_model("assets/camaro.obj");
  pirate_ship_.load_model("assets/pirate_ship.obj");
}


void apeiron::example::World::reset()
{
  camera_.reset();
}


void apeiron::example::World::update(float delta_time, const engine::Input* input)
{
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
}


void apeiron::example::World::render(float time)
{
  frame_++;
  if (options_->autorotate)
    frame_time_ = time;

  renderer_.set_projection(glm::perspective(glm::radians(45.0f), 1280.0f / 720.0f, 0.1f, 1000.0f));
  renderer_.set_view(camera_.view());

  renderer_.set_wireframe(options_->wireframe);

  if (options_->strobe && (frame_ % 8 < 4))
    renderer_.set_wireframe(true);
  else if (options_->strobe)
    renderer_.set_wireframe(false);

  if (options_->pirate_mode)
    renderer_.render(pirate_ship_, options_->main_color);
  else
    renderer_.render(car_, options_->main_color);
}

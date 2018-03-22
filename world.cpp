#include "world.h"


#include "GL/glew.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>


void apeiron::World::init()
{
  shader_.load("shader/mvp_position.vs", "shader/uniform_color.fs");
  car_.load("assets/camaro.obj");
}


void apeiron::World::reset()
{
  camera_.reset();
}


void apeiron::World::update(float delta_time, const Input* input)
{
  if (input) {
    auto distance = options_->velocity * delta_time;
    if (input->forward)
      camera_.move(Camera::Direction::Forward, distance);
    if (input->backward)
      camera_.move(Camera::Direction::Backward, distance);
    if (input->left)
      camera_.move(Camera::Direction::Left, distance);
    if (input->right)
      camera_.move(Camera::Direction::Right, distance);

    camera_.orient(input->mouse_x_rel, input->mouse_y_rel, options_->sensitivity);
  }

  if (cylinder_.points() != options_->cylinder_points) {
    cylinder_.construct(options_->cylinder_points);
  }
}


void apeiron::World::render(float time)
{
  frame_++;
  if (options_->autorotate)
    frame_time_ = time;

  glm::mat4 projection = glm::perspective(glm::radians(45.0f), 1280.0f / 720.0f, 0.1f, 1000.0f);
  glm::mat4 view = camera_.view();

  shader_.use();
  shader_.set_uniform("projection", projection);
  shader_.set_uniform("view", view);

  if (options_->wireframe)
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

  if (options_->strobe && (frame_ % 8 < 4))
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  else if (options_->strobe)
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

  {
    glm::mat4 model;
    shader_.set_uniform("model", model);
    const auto& color = options_->main_color;
    shader_.set_uniform("color", color.r, color.g, color.b, color.a);
    car_.render();
  }

  {
    glm::mat4 model;
    model = glm::translate(model, glm::vec3(0.0f, 1.0f, -10.0f));
    model = glm::rotate(model, frame_time_ * glm::radians(50.0f), glm::vec3(0.5f, 1.0f, 0.0f));
    shader_.set_uniform("model", model);
    const auto& color = options_->main_color;
    shader_.set_uniform("color", color.r, color.g, color.b, color.a);
    cube_.render();
  }

  {
    glm::mat4 model;
    model = glm::translate(model, glm::vec3(0.0f, 1.0f, -5.0f));
    model = glm::rotate(model, frame_time_ * glm::radians(50.0f), glm::vec3(0.5f, 1.0f, 0.0f));
    shader_.set_uniform("model", model);
    const auto& color = options_->main_color;
    shader_.set_uniform("color", color.r, color.g, color.b, color.a);
    cylinder_.render();
  }

  {
    glm::mat4 model;
    float height_scale = 0.1f;
    float width_scale = 3.6f;
    float length_scale = 100.0f;
    model = glm::scale(model, glm::vec3(width_scale, height_scale, length_scale));
    model = glm::translate(model, glm::vec3(0.0f, -0.5f*height_scale, -0.2f));
    shader_.set_uniform("model", model);
    shader_.set_uniform("color", 0.2f, 0.2f, 0.2f, 1.0f);
    // Always fill ground
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    cube_.render();
  }

  glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

#include "renderer.h"


#include "GL/glew.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>


namespace {


glm::mat4 apply_rotation(glm::mat4 model, const glm::vec3& rotation)
{
  model = glm::rotate(model, rotation.x, glm::vec3(1.0f, 0.0f, 0.0f));
  model = glm::rotate(model, rotation.y, glm::vec3(0.0f, 1.0f, 0.0f));
  model = glm::rotate(model, rotation.z, glm::vec3(0.0f, 0.0f, 1.0f));
  return model;
}


}  // namespace


void apeiron::opengl::Renderer::init()
{
  color_shader_.load("shader/mvp_position.vs", "shader/uniform_color.fs");
}


void apeiron::opengl::Renderer::set_projection(glm::mat4 projection)
{
  color_shader_.use();
  color_shader_.set_uniform("projection", projection);
}


void apeiron::opengl::Renderer::set_view(glm::mat4 view)
{
  color_shader_.use();
  color_shader_.set_uniform("view", view);
}


void apeiron::opengl::Renderer::set_wireframe(bool wireframe)
{
  if (wireframe)
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  else
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}


void apeiron::opengl::Renderer::render(const engine::Entity& entity, const engine::Color& color)
{
  glm::mat4 model;
  model = glm::scale(model, entity.scale());
  model = glm::translate(model, entity.position());
  model = apply_rotation(model, entity.rotation());
  color_shader_.use();
  color_shader_.set_uniform("model", model);
  color_shader_.set_uniform("color", color);
  entity.render();
}

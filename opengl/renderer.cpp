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
  shader_.load("shader/vertex.vs", "shader/fragment.fs");
  shader_.use();
  shader_.set_uniform("texture2d", 0);
  shader_.set_uniform("color_mode", 0xFF);
}


void apeiron::opengl::Renderer::use_texture_shading()
{
  shader_.set_uniform("color_mode", 0);
}


void apeiron::opengl::Renderer::use_vertex_color_shading()
{
  shader_.set_uniform("color_mode", 1);
}


void apeiron::opengl::Renderer::use_color_shading()
{
  shader_.set_uniform("color_mode", 2);
}


void apeiron::opengl::Renderer::set_projection(const glm::mat4& projection)
{
  shader_.set_uniform("projection", projection);
}


void apeiron::opengl::Renderer::set_view(const glm::mat4& view)
{
  shader_.set_uniform("view", view);
}


void apeiron::opengl::Renderer::set_wireframe(bool wireframe)
{
  if (wireframe)
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  else
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}


void apeiron::opengl::Renderer::set_lighting(bool lighting)
{
  shader_.set_uniform("light_mode", lighting ? 1 : 0);
}


void apeiron::opengl::Renderer::set_light_position(const glm::vec3& position)
{
  shader_.set_uniform("light_position", position);
}


void apeiron::opengl::Renderer::set_light_color(const glm::vec3& color)
{
  shader_.set_uniform("light_color", color);
}


void apeiron::opengl::Renderer::render(const engine::Entity& entity, const engine::Color& color)
{
  glm::mat4 model;
  model = glm::scale(model, entity.scale());
  model = glm::translate(model, entity.position());
  model = apply_rotation(model, entity.rotation());
  shader_.set_uniform("model", model);
  shader_.set_uniform("color", color);
  entity.render();
}


void apeiron::opengl::Renderer::render(const engine::Entity& entity)
{
  glm::mat4 model;
  model = glm::scale(model, entity.scale());
  model = glm::translate(model, entity.position());
  model = apply_rotation(model, entity.rotation());
  shader_.set_uniform("model", model);
  entity.render();
}

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


void apeiron::opengl::Renderer::render(const engine::Entity& entity)
{
  glm::mat4 model{1.0f};
  model = glm::translate(model, entity.position());
  model = glm::scale(model, entity.scale());
  model = apply_rotation(model, entity.rotation());
  shader_.set_uniform("model", model);
  entity.render();
}


void apeiron::opengl::Renderer::render(const engine::Entity& entity, const glm::vec4& color)
{
  glm::mat4 model{1.0f};
  model = glm::translate(model, entity.position());
  model = glm::scale(model, entity.scale());
  model = apply_rotation(model, entity.rotation());
  shader_.set_uniform("model", model);
  shader_.set_uniform("color", color);
  entity.render();
}


void apeiron::opengl::Renderer::render(const engine::Text& text, const opengl::Charset& charset)
{
  use_texture_shading();
  charset.bind();

  float offset = 0.0f;
  for (char c : text) {
    glm::mat4 model{1.0f};
    model = glm::translate(model, text.position() + text.center() + glm::vec3{offset, 0.0f, 0.0f});
    model = glm::scale(model, text.scale());
    model = apply_rotation(model, text.rotation());
    shader_.set_uniform("model", model);
    charset.render(c);
    offset += charset.character_width() * text.size() * text.spacing().x;
  }
}


void apeiron::opengl::Renderer::render_bounds(const engine::Entity& entity, const glm::vec4& color)
{
  glm::mat4 model{1.0f};
  model = glm::translate(model, entity.position() + entity.center());
  model = glm::scale(model, entity.scale());
  model = apply_rotation(model, entity.rotation());
  shader_.set_uniform("model", model);
  shader_.set_uniform("color", color);
  entity.render_bounds();
}

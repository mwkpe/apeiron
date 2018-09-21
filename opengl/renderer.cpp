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


void apeiron::opengl::Renderer::init(float screen_width, float screen_height)
{
  world_shader_.load("shader/world.vs", "shader/color.fs");
  screen_shader_.load("shader/screen.vs", "shader/color.fs");
  use_screen_space();
  set_screen_center(glm::vec2{screen_width * 0.5f, screen_height * 0.5f});
  use_world_space();
}


void apeiron::opengl::Renderer::use_world_space()
{
  world_shader_.use();
  world_shader_.set_uniform("texture2d", 0);
  world_shader_.set_uniform("color_mode", 0xFF);
  current_shader_ = &world_shader_;
}


void apeiron::opengl::Renderer::use_screen_space()
{
  screen_shader_.use();
  screen_shader_.set_uniform("texture2d", 0);
  screen_shader_.set_uniform("color_mode", 0xFF);
  current_shader_ = &screen_shader_;
}


void apeiron::opengl::Renderer::use_texture_shading()
{
  current_shader_->set_uniform("color_mode", 0);
}


void apeiron::opengl::Renderer::use_vertex_color_shading()
{
  current_shader_->set_uniform("color_mode", 1);
}


void apeiron::opengl::Renderer::use_color_shading()
{
  current_shader_->set_uniform("color_mode", 2);
}


void apeiron::opengl::Renderer::set_screen_center(const glm::vec2& screen_center)
{
  current_shader_->set_uniform("screen_center", screen_center);
}


void apeiron::opengl::Renderer::set_projection(const glm::mat4& projection)
{
  current_shader_->set_uniform("projection", projection);
}


void apeiron::opengl::Renderer::set_view(const glm::mat4& view)
{
  current_shader_->set_uniform("view", view);
}


void apeiron::opengl::Renderer::set_wireframe(bool wireframe)
{
  if (wireframe)
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  else
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}


void apeiron::opengl::Renderer::set_colorize(bool colorize)
{
  current_shader_->set_uniform("colorize", colorize);
}


void apeiron::opengl::Renderer::set_lighting(bool lighting)
{
  current_shader_->set_uniform("light_mode", lighting ? 1 : 0);
}


void apeiron::opengl::Renderer::set_light_position(const glm::vec3& position)
{
  current_shader_->set_uniform("light_position", position);
}


void apeiron::opengl::Renderer::set_light_color(const glm::vec3& color)
{
  current_shader_->set_uniform("light_color", color);
}


void apeiron::opengl::Renderer::render(const engine::Entity& entity)
{
  glm::mat4 model{1.0f};
  model = glm::translate(model, entity.position());
  model = glm::scale(model, entity.scale());
  model = apply_rotation(model, entity.rotation());
  current_shader_->set_uniform("model", model);
  entity.render();
}


void apeiron::opengl::Renderer::render(const engine::Entity& entity, const glm::vec4& color)
{
  glm::mat4 model{1.0f};
  model = glm::translate(model, entity.position());
  model = glm::scale(model, entity.scale());
  model = apply_rotation(model, entity.rotation());
  current_shader_->set_uniform("model", model);
  current_shader_->set_uniform("color", color);
  entity.render();
}


void apeiron::opengl::Renderer::render(const engine::Text& text, const opengl::Tileset& charset)
{
  use_texture_shading();
  charset.bind();

  float offset = 0.0f;
  for (char c : text) {
    glm::mat4 model{1.0f};
    model = glm::translate(model, text.position() + text.center() + glm::vec3{offset, 0.0f, 0.0f});
    model = glm::scale(model, text.scale());
    model = apply_rotation(model, text.rotation());
    current_shader_->set_uniform("model", model);
    charset.render(c);
    offset += charset.tile_width() * text.size() * text.spacing().x;
  }
}


void apeiron::opengl::Renderer::render(const engine::Text& text, const opengl::Tileset& charset,
    const glm::vec4& color)
{
  use_texture_shading();
  set_colorize(true);
  current_shader_->set_uniform("color", color);
  charset.bind();

  float offset = 0.0f;
  for (char c : text) {
    glm::mat4 model{1.0f};
    model = glm::translate(model, text.position() + text.center() + glm::vec3{offset, 0.0f, 0.0f});
    model = glm::scale(model, text.scale());
    model = apply_rotation(model, text.rotation());
    current_shader_->set_uniform("model", model);
    charset.render(c);
    offset += charset.tile_width() * text.size() * text.spacing().x;
  }

  set_colorize(false);
}


void apeiron::opengl::Renderer::render_screen(const engine::Text& text,
    const opengl::Tileset& charset, const glm::vec4& color)
{
  use_texture_shading();
  charset.bind();
  set_colorize(true);
  current_shader_->set_uniform("color", color);
  // Flip y for quick fix
  current_shader_->set_uniform("scale", glm::vec3{text.size(), text.size(), 1.0f});

  float offset = 0.0f;
  auto pos = text.position();
  for (char c : text) {
    current_shader_->set_uniform("translation", glm::vec3{pos.x + offset, pos.y, pos.z});
    charset.render(c);
    offset += charset.tile_width() * text.size() * text.spacing().x;
  }
  set_colorize(false);
}


void apeiron::opengl::Renderer::render_bounds(const engine::Entity& entity, const glm::vec4& color)
{
  glm::mat4 model{1.0f};
  model = glm::translate(model, entity.position() + entity.center());
  model = glm::scale(model, entity.scale());
  model = apply_rotation(model, entity.rotation());
  current_shader_->set_uniform("model", model);
  current_shader_->set_uniform("color", color);
  entity.render_bounds();
}

#include "renderer.h"


#include <glad/glad.h>
#include <glm/gtc/matrix_transform.hpp>


void apeiron::opengl::Renderer::init()
{
  shader_.load("shader/default.vs", "shader/default.fs");
  shader_.use();

  // Init uniforms
  use_color_shading();
  shader_.set_uniform("color", glm::vec4{1.0f, 0.0f, 1.0f, 1.0f});
  shader_.set_uniform("texture2d", 0);

  use_world_space();

  enable_lighting(false);
  enable_color_multiplication(false);
  enable_color_desaturation(false);
  enable_color_inversion(false);

  set_light_position(glm::vec3{0.0f});
  set_light_color(glm::vec4{1.0f, 0.0f, 1.0f, 1.0f});
  set_color_desaturation_strength(0.0f);

  enable_gl_depth_test(false);

  glCullFace(GL_BACK);
  glEnable(GL_CULL_FACE);

  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}


void apeiron::opengl::Renderer::use() const
{
  shader_.use();
}


void apeiron::opengl::Renderer::enable_gl_wireframe(bool enable)
{
  if (enable) {
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  }
  else {
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
  }
}


void apeiron::opengl::Renderer::enable_gl_depth_test(bool enable)
{
  if (enable) {
    glEnable(GL_DEPTH_TEST);
  }
  else {
    glDisable(GL_DEPTH_TEST);
  }
}


void apeiron::opengl::Renderer::enable_gl_blend(bool enable)
{
  if (enable) {
    glEnable(GL_BLEND);
  }
  else {
    glDisable(GL_BLEND);
  }
}


void apeiron::opengl::Renderer::set_gl_viewport(std::int32_t x, std::int32_t y,
    std::int32_t w, std::int32_t h)
{
  glViewport(x, y, w, h);
}


void apeiron::opengl::Renderer::set_gl_frame_buffer(std::uint32_t id)
{
  glBindFramebuffer(GL_FRAMEBUFFER, id);
}


void apeiron::opengl::Renderer::set_gl_color_mask(bool r, bool g, bool b, bool a)
{
  glColorMask(r, g, b, a);
}


void apeiron::opengl::Renderer::gl_clear(float r, float g, float b)
{
  glClearColor(r, g, b, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
}


void apeiron::opengl::Renderer::use_world_space()
{
  shader_.set_uniform("render_mode", 0);
}


void apeiron::opengl::Renderer::use_screen_space()
{
  shader_.set_uniform("render_mode", 1);
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


void apeiron::opengl::Renderer::set_world_view_projection()
{
  world_view_projection_ = world_projection_ * world_view_;
  shader_.set_uniform("world_view_projection", world_view_projection_);
}


void apeiron::opengl::Renderer::set_screen_projection(float width, float height)
{
  shader_.set_uniform("screen_projection", glm::ortho(0.0f, width, 0.0f, height));
}


void apeiron::opengl::Renderer::enable_lighting(bool enable)
{
  shader_.set_uniform("lighting_enabled", enable);
}


void apeiron::opengl::Renderer::enable_color_multiplication(bool enable)
{
  shader_.set_uniform("color_multiplication_enabled", enable);
}


void apeiron::opengl::Renderer::enable_color_desaturation(bool enable)
{
  shader_.set_uniform("color_desaturation_enabled", enable);
}


void apeiron::opengl::Renderer::enable_color_inversion(bool enable)
{
  shader_.set_uniform("color_inversion_enabled", enable);
}


void apeiron::opengl::Renderer::set_light_position(const glm::vec3& position)
{
  shader_.set_uniform("light_position", position);
}


void apeiron::opengl::Renderer::set_light_color(const glm::vec4& color)
{
  shader_.set_uniform("light_color", color);
}


void apeiron::opengl::Renderer::set_color_desaturation_strength(float strength)
{
  shader_.set_uniform("color_desaturation_strength", strength);
}


void apeiron::opengl::Renderer::render(const engine::Entity& entity)
{
  shader_.set_uniform("model", entity.transform().model_matrix());
  entity.render();
}


void apeiron::opengl::Renderer::render(const engine::Entity& entity, const glm::vec4& color)
{
  shader_.set_uniform("model", entity.transform().model_matrix());
  shader_.set_uniform("color", color);
  entity.render();
}


void apeiron::opengl::Renderer::render(const engine::Entity& entity,
    const opengl::Tileset& tileset, std::uint32_t index)
{
  use_texture_shading();
  tileset.bind();
  shader_.set_uniform("model", entity.transform().model_matrix());
  tileset.render(index);
}


void apeiron::opengl::Renderer::render(const engine::Entity& entity,
    const opengl::Meshset& meshset, std::uint32_t index)
{
  use_vertex_color_shading();
  shader_.set_uniform("model", entity.transform().model_matrix());
  meshset.render(index);
}


void apeiron::opengl::Renderer::render(const engine::Entity& entity,
    const opengl::Meshset& meshset, std::uint32_t index, const glm::vec4& color, bool colorize)
{
  if (colorize) {
    use_vertex_color_shading();
    enable_color_multiplication();
  }
  else {
    use_color_shading();
  }

  shader_.set_uniform("color", color);
  shader_.set_uniform("model", entity.transform().model_matrix());

  meshset.render(index);
  enable_color_multiplication(false);
}


void apeiron::opengl::Renderer::render_screen(const engine::Entity& entity)
{
  shader_.set_uniform("translation", entity.transform().position());
  shader_.set_uniform("scale", entity.transform().scale());
  entity.render();
}


void apeiron::opengl::Renderer::render_screen(const engine::Entity& entity, const glm::vec4& color)
{
  shader_.set_uniform("translation", entity.transform().position());
  shader_.set_uniform("scale", entity.transform().scale());
  shader_.set_uniform("color", color);
  entity.render();
}


void apeiron::opengl::Renderer::render_screen(const engine::Entity& entity,
    const opengl::Meshset& meshset, std::uint32_t index)
{
  use_vertex_color_shading();

  shader_.set_uniform("translation", entity.transform().position());
  shader_.set_uniform("scale", entity.transform().scale());

  meshset.render(index);
}


void apeiron::opengl::Renderer::render_screen(const engine::Entity& entity,
    const opengl::Meshset& meshset, std::uint32_t index, const glm::vec4& color, bool colorize)
{
  if (colorize) {
    use_vertex_color_shading();
    enable_color_multiplication();
  }
  else {
    use_color_shading();
  }

  shader_.set_uniform("color", color);
  shader_.set_uniform("translation", entity.transform().position());
  shader_.set_uniform("scale", entity.transform().scale());

  meshset.render(index);
  enable_color_multiplication(false);
}

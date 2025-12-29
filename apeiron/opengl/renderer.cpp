#include "renderer.h"


#include <glad/glad.h>


void apeiron::opengl::Renderer::init()
{
  shader_.load("shader/default.vs", "shader/default.fs");
  shader_.use();
  shader_.set_uniform("render_mode", 0);
  shader_.set_uniform("clip_scene", false);
  shader_.set_uniform("colorize", false);
  shader_.set_uniform("desaturate", false);
  shader_.set_uniform("clip_scene", false);
  shader_.set_uniform("color_mode", 0xFF);
  shader_.set_uniform("texture2d", 0);
}


void apeiron::opengl::Renderer::use()
{
  shader_.use();
}


void apeiron::opengl::Renderer::set_viewport(int x, int y, int w, int h) const
{
  glViewport(x, y, w, h);
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


void apeiron::opengl::Renderer::set_view(const glm::mat4& view)
{
  shader_.set_uniform("view", view);
}


void apeiron::opengl::Renderer::set_projection(const glm::mat4& projection)
{
  shader_.set_uniform("projection", projection);
}


void apeiron::opengl::Renderer::set_ortho_projection(float width, float height)
{
  shader_.set_uniform("projection", glm::ortho(0.0f, width, 0.0f, height));
}


void apeiron::opengl::Renderer::set_view_projection()
{
  view_projection_ = projection_ * view_;
  shader_.set_uniform("view_projection", view_projection_);
}


void apeiron::opengl::Renderer::set_clip_scene(bool clip_scene)
{
  if (clip_scene) {
    glEnable(GL_CLIP_DISTANCE0);
  }
  else {
    glDisable(GL_CLIP_DISTANCE0);
  }

  shader_.set_uniform("clip_scene", clip_scene);
}


void apeiron::opengl::Renderer::set_clipping_plane(const glm::vec4& plane)
{
  shader_.set_uniform("clipping_plane", plane);
}


void apeiron::opengl::Renderer::set_wireframe(bool wireframe) const
{
  if (wireframe) {
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  }
  else {
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
  }
}


void apeiron::opengl::Renderer::set_depth_test(bool depth_test) const
{
  if (depth_test) {
    glEnable(GL_DEPTH_TEST);
  }
  else {
    glDisable(GL_DEPTH_TEST);
  }
}


void apeiron::opengl::Renderer::set_blend(bool blend) const
{
  if (blend) {
    glEnable(GL_BLEND);
  }
  else {
    glDisable(GL_BLEND);
  }
}


void apeiron::opengl::Renderer::set_colorize(bool colorize)
{
  shader_.set_uniform("colorize", colorize);
}


void apeiron::opengl::Renderer::set_invert_color(bool invert)
{
  shader_.set_uniform("invert_color", invert);
}


void apeiron::opengl::Renderer::set_desaturate(bool desaturate)
{
  shader_.set_uniform("desaturate", desaturate);
}


void apeiron::opengl::Renderer::set_desaturation_factor(float desaturation_factor)
{
  shader_.set_uniform("desaturation_factor", desaturation_factor);
}


void apeiron::opengl::Renderer::set_lighting(bool lighting)
{
  shader_.set_uniform("light_mode", lighting ? 1 : 0);
}


void apeiron::opengl::Renderer::set_light_position(const glm::vec3& position)
{
  shader_.set_uniform("light_position", position);
}


void apeiron::opengl::Renderer::set_light_color(const glm::vec4& color)
{
  shader_.set_uniform("light_color", color);
}


void apeiron::opengl::Renderer::clear() const
{
  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
}


void apeiron::opengl::Renderer::clear(float r, float g, float b) const
{
  glClearColor(r, g, b, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
}


void apeiron::opengl::Renderer::clear(const glm::vec3& color) const
{
  glClearColor(color.r, color.g, color.b, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
}


void apeiron::opengl::Renderer::clear(const glm::vec4& color) const
{
  glClearColor(color.r, color.g, color.b, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
}


void apeiron::opengl::Renderer::clear_depth_buffer() const
{
  glClear(GL_DEPTH_BUFFER_BIT);
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
    set_colorize(true);
  }
  else {
    use_color_shading();
  }

  shader_.set_uniform("color", color);
  shader_.set_uniform("model", entity.transform().model_matrix());

  meshset.render(index);
  set_colorize(false);
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
    set_colorize(true);
  }
  else {
    use_color_shading();
  }

  shader_.set_uniform("color", color);
  shader_.set_uniform("translation", entity.transform().position());
  shader_.set_uniform("scale", entity.transform().scale());

  meshset.render(index);
  set_colorize(false);
}

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

  glCullFace(GL_BACK);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  glEnable(GL_DEPTH_TEST);
  glEnable(GL_CULL_FACE);
}


void apeiron::opengl::Renderer::use()
{
  shader_.use();
}


void apeiron::opengl::Renderer::set_gl_viewport(std::int32_t x, std::int32_t y,
    std::int32_t w, std::int32_t h)
{
  glViewport(x, y, w, h);
}


void apeiron::opengl::Renderer::set_gl_frame_buffer(std::int32_t id)
{
  glBindFramebuffer(GL_FRAMEBUFFER, id);
}


void apeiron::opengl::Renderer::set_gl_wireframe(bool wireframe)
{
  if (wireframe) {
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  }
  else {
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
  }
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


void apeiron::opengl::Renderer::set_desaturation_strength(float strength)
{
  shader_.set_uniform("desaturation_strength", strength);
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

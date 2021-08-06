#ifndef APEIRON_OPENGL_RENDERER_H
#define APEIRON_OPENGL_RENDERER_H


#include <glm/glm.hpp>
#include "opengl/shader.h"
#include "opengl/shape.h"
#include "opengl/tileset.h"
#include "engine/entity.h"
#include "engine/text.h"


namespace apeiron::opengl {


class Renderer final
{
public:
  void init();
  void use();
  void set_viewport(int x, int y, int w, int h);

  void use_world_space();
  void use_screen_space();
  void use_texture_shading();
  void use_color_shading();
  void use_vertex_color_shading();

  void preset_view(const glm::mat4& view) { view_ = view; }
  void preset_projection(const glm::mat4& projection) { projection_ = projection; }

  void set_view(const glm::mat4& view);
  void set_projection(const glm::mat4& projection);
  void set_view_projection();
  void set_clip_scene(bool clip_scene);
  void set_clipping_plane(const glm::vec4& plane);
  void set_wireframe(bool wireframe);
  void set_depth_test(bool depth_test);
  void set_colorize(bool colorize);
  void set_lighting(bool lighting);
  void set_light_position(const glm::vec3& position);
  void set_light_color(const glm::vec4& color);

  void clear() const;
  void clear(float r, float g, float b) const;

  void render(const engine::Entity& entity);
  void render(const engine::Entity& entity, const glm::vec4& color);
  void render(const engine::Text& text, const opengl::Tileset& charset);
  void render(const engine::Text& text, const opengl::Tileset& charset, const glm::vec4& color);
  void render_screen(const engine::Entity& entity);
  void render_screen(const engine::Entity& entity, const glm::vec4& color);
  void render_screen(const engine::Text& text, const opengl::Tileset& charset,
      const glm::vec4& color);
  void render_bounds(const engine::Entity& entity, const glm::vec4& color);

  glm::mat4 view_projection() { return view_projection_; }
  glm::mat4 inverse_view_projection() { return glm::inverse(view_projection_); }

private:
  Shader shader_;
  glm::mat4 view_;
  glm::mat4 projection_;
  glm::mat4 view_projection_;
};


}  // namespace apeiron::opengl


#endif  // APEIRON_OPENGL_RENDERER_H

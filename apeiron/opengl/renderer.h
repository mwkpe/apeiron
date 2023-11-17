#ifndef APEIRON_OPENGL_RENDERER_H
#define APEIRON_OPENGL_RENDERER_H


// This is just the default/example renderer. Ideally you write your own, or better, use a proper
// library. It's neither complete nor consistent in some aspects. Some render functions may expect
// certain perspective, camera and object configurations to work properly.


#include <glm/glm.hpp>

#include "apeiron/engine/entity.h"
#include "apeiron/engine/text.h"

#include "apeiron/opengl/mesh_font.h"
#include "apeiron/opengl/meshset.h"
#include "apeiron/opengl/shader.h"
#include "apeiron/opengl/shape.h"
#include "apeiron/opengl/tileset.h"


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
  void set_ortho_projection(float width, float height);
  void set_view_projection();
  void set_clip_scene(bool clip_scene);
  void set_clipping_plane(const glm::vec4& plane);
  void set_wireframe(bool wireframe);
  void set_depth_test(bool depth_test);
  void set_blend(bool blend);
  void set_colorize(bool colorize);
  void set_invert_color(bool invert);
  void set_desaturate(bool desaturate);
  void set_desaturation_factor(float desaturation_factor);
  void set_lighting(bool lighting);
  void set_light_position(const glm::vec3& position);
  void set_light_color(const glm::vec4& color);

  void clear() const;
  void clear(float r, float g, float b) const;
  void clear(const glm::vec3& color) const;
  void clear(const glm::vec4& color) const;
  void clear_depth_buffer() const;

  void render(const engine::Entity& entity);
  void render(const engine::Entity& entity, const glm::vec4& color);
  void render(const engine::Entity& entity, const opengl::Tileset& tileset, std::uint32_t index);
  void render(const engine::Entity& entity, const opengl::Meshset& meshset, std::uint32_t index);
  void render(const engine::Entity& entity, const opengl::Meshset& meshset, std::uint32_t index,
      const glm::vec3& offset);
  void render(const engine::Entity& entity, const opengl::Meshset& meshset, std::uint32_t index,
      const glm::vec4& color, bool colorize = false);

  template<typename T> void render_text(const T& text, const opengl::Tileset& charset);
  template<typename T> void render_text(const T& text, const opengl::Tileset& charset,
      const glm::vec4& color);
  template<typename T> void render_text(const T& text, const opengl::Mesh_font& charset,
      const glm::vec4& color);
  template<typename T> void render_text(const T& text, const opengl::Meshset& charset,
      const glm::vec4& color);

  void render_screen(const engine::Entity& entity);
  void render_screen(const engine::Entity& entity, const glm::vec4& color);
  void render_screen(const engine::Entity& entity, const opengl::Meshset& meshset,
      std::uint32_t index);
  void render_screen(const engine::Entity& entity, const opengl::Meshset& meshset,
      std::uint32_t index, const glm::vec4& color, bool colorize = false);
  void render_screen(const engine::Text& text, const opengl::Tileset& charset,
      const glm::vec4& color);
  void render_screen(const engine::Text& text, const opengl::Mesh_font& charset,
      const glm::vec4& color);
  void render_screen(const engine::Text& text, const opengl::Meshset& charset,
      const glm::vec4& color);
  void render_bounds(const engine::Entity& entity, const glm::vec4& color);

  glm::mat4 view_projection() { return view_projection_; }
  glm::mat4 inverse_view_projection() { return glm::inverse(view_projection_); }

  Shader& shader() { return shader_; }

private:
  Shader shader_;
  glm::mat4 view_;
  glm::mat4 projection_;
  glm::mat4 view_projection_;
};


}  // namespace apeiron::opengl


#endif  // APEIRON_OPENGL_RENDERER_H

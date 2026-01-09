#ifndef APEIRON_OPENGL_RENDERER_H
#define APEIRON_OPENGL_RENDERER_H


// This is just a default/example renderer


#include <glm/glm.hpp>

#include "apeiron/engine/entity.h"
#include "apeiron/opengl/meshset.h"
#include "apeiron/opengl/shader.h"
#include "apeiron/opengl/tileset.h"
#include "apeiron/opengl/vertex_array.h"


namespace apeiron::opengl {


class Renderer final
{
public:
  void init();
  void use();

  // OpenGL
  static void set_gl_viewport(std::int32_t x, std::int32_t y, std::int32_t w, std::int32_t h);
  static void set_gl_frame_buffer(std::int32_t id);
  static void set_gl_wireframe(bool wireframe);
  static void set_gl_color_mask(bool r, bool g, bool b, bool a);
  static void gl_clear(float r, float g, float b);

  void use_world_space();
  void use_screen_space();
  void use_texture_shading();
  void use_vertex_color_shading();
  void use_color_shading();

  void preset_view(const glm::mat4& view) { view_ = view; }
  void preset_projection(const glm::mat4& projection) { projection_ = projection; }

  void set_view(const glm::mat4& view);
  void set_projection(const glm::mat4& projection);
  void set_ortho_projection(float width, float height);
  void set_view_projection();

  void set_colorize(bool colorize);
  void set_invert_color(bool invert);
  void set_desaturate(bool desaturate);
  void set_desaturation_strength(float strength);

  void set_lighting(bool lighting);
  void set_light_position(const glm::vec3& position);
  void set_light_color(const glm::vec4& color);

  void render(const engine::Entity& entity);
  void render(const engine::Entity& entity, const glm::vec4& color);
  void render(const engine::Entity& entity, const opengl::Tileset& tileset, std::uint32_t index);
  void render(const engine::Entity& entity, const opengl::Meshset& meshset, std::uint32_t index);
  void render(const engine::Entity& entity, const opengl::Meshset& meshset, std::uint32_t index,
      const glm::vec4& color, bool colorize = false);

  void render_screen(const engine::Entity& entity);
  void render_screen(const engine::Entity& entity, const glm::vec4& color);
  void render_screen(const engine::Entity& entity, const opengl::Meshset& meshset,
      std::uint32_t index);
  void render_screen(const engine::Entity& entity, const opengl::Meshset& meshset,
      std::uint32_t index, const glm::vec4& color, bool colorize = false);

  [[nodiscard]] glm::mat4 view_projection() { return view_projection_; }
  [[nodiscard]] glm::mat4 inverse_view_projection() { return glm::inverse(view_projection_); }

  Shader& shader() { return shader_; }

private:
  Shader shader_;
  glm::mat4 view_ = glm::mat4{0.0f};
  glm::mat4 projection_ = glm::mat4{0.0f};
  glm::mat4 view_projection_ = glm::mat4{0.0f};
};


}  // namespace apeiron::opengl


#endif  // APEIRON_OPENGL_RENDERER_H

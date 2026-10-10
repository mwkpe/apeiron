#ifndef APEIRON_OPENGL_RENDERER_H
#define APEIRON_OPENGL_RENDERER_H


// This is just a default/example renderer

#include <cstdint>

#include <glm/glm.hpp>

#include "apeiron/engine/entity.h"
#include "apeiron/opengl/meshset.h"
#include "apeiron/opengl/shader.h"
#include "apeiron/opengl/tileset.h"


namespace apeiron::opengl {


class Renderer final
{
public:
  void init();
  void use() const;

  // OpenGL
  static void enable_gl_wireframe(bool enable = true);
  static void enable_gl_depth_test(bool enable = true);
  static void enable_gl_blend(bool enable = true);

  static void set_gl_viewport(std::int32_t x, std::int32_t y, std::int32_t w, std::int32_t h);
  static void set_gl_frame_buffer(std::uint32_t id);
  static void set_gl_color_mask(bool r, bool g, bool b, bool a);

  static void gl_clear(float r, float g, float b);

  void use_world_space();
  void use_screen_space();
  void use_texture_shading();
  void use_vertex_color_shading();
  void use_color_shading();

  void set_world_view(const glm::mat4& view) { world_view_ = view; }
  void set_world_projection(const glm::mat4& projection) { world_projection_ = projection; }
  void set_world_view_projection();
  void set_screen_projection(float width, float height);

  void enable_lighting(bool enable = true);
  void enable_color_multiplication(bool enable = true);
  void enable_color_desaturation(bool enable = true);
  void enable_color_inversion(bool enable = true);

  void set_light_position(const glm::vec3& position);
  void set_light_color(const glm::vec4& color);
  void set_color_desaturation_strength(float strength);

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

  [[nodiscard]] const glm::mat4& world_view_projection() const { return world_view_projection_; }
  [[nodiscard]] glm::mat4 inverse_world_view_projection() const {
      return glm::inverse(world_view_projection_); }

  Shader& shader() { return shader_; }

private:
  Shader shader_;
  glm::mat4 world_view_ = glm::mat4{1.0f};
  glm::mat4 world_projection_ = glm::mat4{1.0f};
  glm::mat4 world_view_projection_ = glm::mat4{1.0f};
};


}  // namespace apeiron::opengl


#endif  // APEIRON_OPENGL_RENDERER_H

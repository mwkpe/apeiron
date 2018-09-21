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
  void init(float screen_width, float screen_height);
  void use_world_space();
  void use_screen_space();
  void use_texture_shading();
  void use_vertex_color_shading();
  void use_color_shading();
  void set_screen_center(const glm::vec2& screen_center);
  void set_projection(const glm::mat4& projection);
  void set_view(const glm::mat4& view);
  void set_wireframe(bool wireframe);
  void set_colorize(bool colorize);
  void set_lighting(bool lighting);
  void set_light_position(const glm::vec3& position);
  void set_light_color(const glm::vec3& color);
  void render(const engine::Entity& entity);
  void render(const engine::Entity& entity, const glm::vec4& color);
  void render(const engine::Text& text, const opengl::Charset& charset);
  void render(const engine::Text& text, const opengl::Charset& charset, const glm::vec4& color);
  void render_screen(const engine::Text& text, const opengl::Charset& charset, const glm::vec4& color);
  void render_bounds(const engine::Entity& entity, const glm::vec4& color);

private:
  Shader world_shader_;
  Shader screen_shader_;
  Shader* current_shader_ = &world_shader_;
};


}  // namespace apeiron::opengl


#endif  // APEIRON_OPENGL_RENDERER_H

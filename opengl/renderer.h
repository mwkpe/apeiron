#ifndef APEIRON_OPENGL_RENDERER_H
#define APEIRON_OPENGL_RENDERER_H


#include <glm/glm.hpp>
#include "opengl/shader.h"
#include "opengl/shape.h"
#include "engine/entity.h"


namespace apeiron::opengl {


class Renderer final
{
public:
  void init();
  void use_texture_shading();
  void use_vertex_color_shading();
  void use_color_shading();
  void set_projection(const glm::mat4& projection);
  void set_view(const glm::mat4& view);
  void set_wireframe(bool wireframe);
  void set_lighting(bool lighting);
  void set_light_position(const glm::vec3& position);
  void set_light_color(const glm::vec3& color);
  void render(const engine::Entity& entity);
  void render(const engine::Entity& entity, const glm::vec4& color);
  void render_bounds(const engine::Entity& entity, const glm::vec4& color);

private:
  Shader shader_;
};


}  // namespace apeiron::opengl


#endif  // APEIRON_OPENGL_RENDERER_H

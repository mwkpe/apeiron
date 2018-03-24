#ifndef APEIRON_OPENGL_RENDERER_H
#define APEIRON_OPENGL_RENDERER_H


#include <glm/glm.hpp>
#include "opengl/shader.h"
#include "opengl/shape.h"
#include "engine/color.h"
#include "engine/entity.h"


namespace apeiron::opengl {


class Renderer final
{
public:
  void init();
  void set_projection(glm::mat4 projection);
  void set_view(glm::mat4 view);
  void set_wireframe(bool wireframe);
  void render(const engine::Entity& entity, const engine::Color& color);

private:
  Shader color_shader_;
};


}  // namespace apeiron::opengl


#endif  // APEIRON_OPENGL_RENDERER_H

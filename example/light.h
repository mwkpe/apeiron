#ifndef APEIRON_EXAMPLE_LIGHT_H
#define APEIRON_EXAMPLE_LIGHT_H


#include <glm/glm.hpp>
#include "engine/entity.h"
#include "opengl/model.h"


namespace apeiron::example {


class Light final : public engine::Entity
{
public:
  explicit Light(const opengl::Model* model) : model_{model} {}
  void set_color(float r, float g, float b) { color_ = glm::vec4{r, g, b, 1.0f}; }
  glm::vec4 color() const { return color_; }
  void render() const override { model_->render(); }

private:
  const opengl::Model* model_;
  glm::vec4 color_ = glm::vec4{1.0f, 1.0f, 1.0f, 1.0f};
};


}  // namespace apeiron::example


#endif  // APEIRON_EXAMPLE_LIGHT_H

#ifndef APEIRON_PREFAB_LIGHT_H
#define APEIRON_PREFAB_LIGHT_H


#include <glm/glm.hpp>
#include "engine/entity.h"
#include "engine/collision.h"
#include "opengl/model.h"


namespace apeiron::prefab {


class Light final : public engine::Entity
{
public:
  explicit Light(const opengl::Model* model = nullptr) : model_{model} {}
  void set_color(float r, float g, float b, float a = 1.0f) { color_ = glm::vec4{r, g, b, a}; };
  void set_color(glm::vec4 color) { color_ = color; };
  void toggle() { on_ = !on_; }
  void switch_on() { on_ = true; }
  void switch_off() { on_ = false; }
  bool is_on() const { return on_; }
  glm::vec4 color() const { return color_; }
  auto collider() const { return engine::collision::Sphere{position_, 0.5f * scale_.x}; }
  void render() const override { if (model_) for (const auto& mesh : *model_) mesh.render(); }

private:
  bool on_ = false;
  glm::vec4 color_ = glm::vec4{1.0f, 0.0f, 1.0f, 1.0f};
  const opengl::Model* model_ = nullptr;
};


}  // namespace apeiron::prefab


#endif  // APEIRON_PREFAB_LIGHT_H

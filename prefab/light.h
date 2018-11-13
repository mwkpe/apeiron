#ifndef APEIRON_PREFAB_LIGHT_H
#define APEIRON_PREFAB_LIGHT_H


#include <glm/glm.hpp>
#include "engine/entity.h"
#include "opengl/model.h"


namespace apeiron::prefab {


class Light final : public engine::Entity
{
public:
  explicit Light(const opengl::Model* model = nullptr) : model_{model} {}
  void toggle() { on_ = !on_; }
  void switch_on() { on_ = true; }
  void switch_off() { on_ = false; }
  bool is_on() { return on_; }
  void render() const override { if (model_) for (const auto& mesh : *model_) mesh.render(); }

private:
  bool on_ = false;
  const opengl::Model* model_ = nullptr;
};


}  // namespace apeiron::prefab


#endif  // APEIRON_PREFAB_LIGHT_H

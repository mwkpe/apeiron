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
  void render() const override { if (model_) model_->render(); }

private:
  const opengl::Model* model_ = nullptr;
};


}  // namespace apeiron::prefab


#endif  // APEIRON_PREFAB_LIGHT_H

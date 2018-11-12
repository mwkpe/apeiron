#ifndef APEIRON_PREFAB_TEAPOT_H
#define APEIRON_PREFAB_TEAPOT_H


#include "engine/entity.h"
#include "opengl/model.h"


namespace apeiron::prefab {


class Teapot final : public engine::Entity
{
public:
  void load_model() { model_.load("assets/utah_teapot.obj"); }
  void render() const override { model_.render();  }

private:
  opengl::Model model_;
};


}  // namespace apeiron::prefab


#endif  // APEIRON_PREFAB_TEAPOT_H

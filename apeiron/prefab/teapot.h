#ifndef APEIRON_PREFAB_TEAPOT_H
#define APEIRON_PREFAB_TEAPOT_H


#include "apeiron/engine/entity.h"
#include "apeiron/engine/vertex.h"
#include "apeiron/opengl/model.h"


namespace apeiron::prefab {


class Teapot final : public engine::Entity
{
public:
  void load_model() { model_.load<engine::Vertex_normal>("assets/models/utah_teapot.obj"); }
  void render() const override { for (const auto& mesh : model_) mesh.render(); }

private:
  opengl::Model model_;
};


}  // namespace apeiron::prefab


#endif  // APEIRON_PREFAB_TEAPOT_H

#ifndef APEIRON_PREFAB_ORIGIN_H
#define APEIRON_PREFAB_ORIGIN_H


#include <glm/glm.hpp>
#include <cstdint>
#include "apeiron/engine/entity.h"
#include "apeiron/opengl/cylinder.h"


namespace apeiron::prefab {


class Origin final : public engine::Entity
{
public:
  void init(int points, float radius, float height);
  void init_rgb(int points, float radius, float height);
  void render() const override;

private:
  opengl::Cylinder x_;
  opengl::Cylinder y_;
  opengl::Cylinder z_;
};


}  // namespace apeiron::prefab


#endif  // APEIRON_PREFAB_ORIGIN_H

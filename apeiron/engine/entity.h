#ifndef APEIRON_ENGINE_ENTITY_H
#define APEIRON_ENGINE_ENTITY_H


#include "apeiron/engine/transform.h"


namespace apeiron::engine {


class Entity
{
public:
  Entity() = default;
  virtual ~Entity() = default;
  virtual void render() const {}
  Transform& transform() { return transform_; }
  const Transform& transform() const { return transform_; }

private:
  engine::Transform transform_;
};


}  // namespace apeiron::engine


#endif  // APEIRON_ENGINE_ENTITY_H

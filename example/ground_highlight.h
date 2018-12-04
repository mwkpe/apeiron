#ifndef APEIRON_EXAMPLE_GROUND_HIGHLIGHT_H
#define APEIRON_EXAMPLE_GROUND_HIGHLIGHT_H


#include <glm/glm.hpp>
#include "engine/entity.h"
#include "opengl/quad.h"


namespace apeiron::example {


class Ground_highlight final : public engine::Entity
{
public:
  Ground_highlight() : quad_{0.8f, 0.8f, engine::Face::Up} {}
  void set_visible(bool visible) { visible_ = visible; }
  bool visible() { return visible_; }
  void render() const override { quad_.render(); }

private:
  opengl::Quad quad_;
  bool visible_ = false;
};


}  // namespace apeiron::example


#endif  // APEIRON_EXAMPLE_GROUND_HIGHLIGHT_H

#ifndef APEIRON_PREFAB_XY_AXES_H
#define APEIRON_PREFAB_XY_AXES_H


#include <cstdint>

#include "apeiron/engine/entity.h"
#include "apeiron/engine/font.h"
#include "apeiron/opengl/mesh.h"
#include "apeiron/opengl/text.h"


namespace apeiron::prefab {


class Xy_axes final : public engine::Entity
{
public:
  template<typename T> void init(const glm::uvec2& size, float width, bool invert_y,
      const engine::Font<T>& font, float font_scale);
  void render() const override { axes_.render(); }
  opengl::Multi_text& tick_labels() { return tick_labels_; }

private:
  opengl::Mesh axes_;
  opengl::Multi_text tick_labels_;
};


}  // namespace apeiron::prefab


#endif  // APEIRON_PREFAB_XY_AXES_H

#ifndef APEIRON_OPENGL_TEXT_H
#define APEIRON_OPENGL_TEXT_H


#include <string>
#include <string_view>

#include <glm/glm.hpp>

#include "apeiron/engine/entity.h"
#include "apeiron/engine/font.h"
#include "apeiron/engine/vertex.h"
#include "apeiron/opengl/meshset.h"


namespace apeiron::opengl {


class Text final : public engine::Entity
{
public:
  bool operator==(std::string_view rhs) const noexcept { return text_ == rhs; }
  bool operator!=(std::string_view rhs) const noexcept { return text_ != rhs; }

  template<typename T = engine::Vertex> void init(std::string_view text,
      const engine::Font<T>& font, opengl::Usage_hint hint = opengl::Usage_hint::Static);
  template<typename T = engine::Vertex> void update(std::string_view text,
      const engine::Font<T>& font);

  void render() const override { meshset_.render(); }

private:
  std::string text_;
  Meshset meshset_;
};


}  // namespace apeiron::opengl


#endif  // APEIRON_OPENGL_TEXT_H

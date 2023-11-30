#ifndef APEIRON_OPENGL_GRID_H
#define APEIRON_OPENGL_GRID_H


#include <glm/glm.hpp>
#include "apeiron/opengl/shape.h"


namespace apeiron::opengl {


class Grid final : public Shape
{
public:
  Grid() = default;
  Grid(const glm::vec2& size, std::size_t x_steps, std::size_t y_steps,
      const glm::vec4& color, float line_width = 1.0f);

  void init(const glm::vec2& size, std::size_t x_steps, std::size_t y_steps,
      const glm::vec4& color, float line_width = 1.0f);
  [[nodiscard]] glm::vec2 size() const { return size_; }
  void render() const override;

private:
  glm::vec2 size_ = glm::vec2{1.0f};
  float line_width_ = 1.0f;
};


}  // namespace apeiron::opengl


#endif  // APEIRON_OPENGL_GRID_H

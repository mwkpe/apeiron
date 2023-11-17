#include "grid.h"


apeiron::prefab::Grid::Grid(const glm::vec2& size, std::size_t x_steps,
    std::size_t y_steps, const glm::vec4& color, float line_width) :
    grid_{size, x_steps, y_steps, color, line_width}
{
}


void apeiron::prefab::Grid::init(const glm::vec2& size, std::size_t x_steps,
    std::size_t y_steps, const glm::vec4& color, float line_width)
{
  grid_.init(size, x_steps, y_steps, color, line_width);
}

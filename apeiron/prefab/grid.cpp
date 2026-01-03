#include "grid.h"


apeiron::prefab::Grid::Grid(const glm::vec2& size, const glm::uvec2& cells,
    const glm::vec4& color, bool edge, float line_width)
    : grid_{size, cells, color, edge, line_width}
{
}


void apeiron::prefab::Grid::init(const glm::vec2& size, const glm::uvec2& cells,
    const glm::vec4& color, bool edge, float line_width)
{
  grid_.init(size, cells, color, edge, line_width);
}

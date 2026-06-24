#include "origin.h"


#include "apeiron/engine/enums.h"
#include "apeiron/engine/vertex.h"


void apeiron::prefab::Origin::init(int points, float radius, float height)
{
  x_.init(points, radius, height, engine::Axis::X);
  y_.init(points, radius, height, engine::Axis::Y);
  z_.init(points, radius, height, engine::Axis::Z);
}


void apeiron::prefab::Origin::init_rgb(int points, float radius, float height)
{
  x_.init(points, radius, height, engine::Axis::X, {1.0f, 0.0f, 0.0f, 1.0f});
  y_.init(points, radius, height, engine::Axis::Y, {0.0f, 1.0f, 0.0f, 1.0f});
  z_.init(points, radius, height, engine::Axis::Z, {0.0f, 0.0f, 1.0f, 1.0f});
}


void apeiron::prefab::Origin::render() const
{
  x_.render();
  y_.render();
  z_.render();
}

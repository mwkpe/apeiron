#include "text.h"


void apeiron::engine::Text::set_size(float size)
{
  set_scale(size, size, size);
}

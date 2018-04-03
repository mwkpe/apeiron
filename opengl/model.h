#ifndef APEIRON_OPENGL_MODEL_H
#define APEIRON_OPENGL_MODEL_H


#include <cstdint>
#include <string_view>
#include "opengl/shape.h"


namespace apeiron::opengl {


class Model final : public Shape
{
public:
  void load(std::string_view filename, std::uint32_t flags);
  void render() const override;
};


}  // namespace apeiron::opengl


#endif  // APEIRON_OPENGL_MODEL_H

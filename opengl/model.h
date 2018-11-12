#ifndef APEIRON_OPENGL_MODEL_H
#define APEIRON_OPENGL_MODEL_H


#include <cstdint>
#include <string_view>
#include "engine/vertex.h"
#include "opengl/shape.h"


namespace apeiron::opengl {


class Model final : public Shape
{
public:
  template<typename T = apeiron::engine::Vertex> void load(std::string_view filename);
  void render() const override;
};


}  // namespace apeiron::opengl


#endif  // APEIRON_OPENGL_MODEL_H

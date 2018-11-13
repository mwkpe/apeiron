#ifndef APEIRON_OPENGL_MESH_H
#define APEIRON_OPENGL_MESH_H


#include <vector>
#include "opengl/shape.h"
#include "engine/vertex.h"


namespace apeiron::opengl {


class Mesh final : public Shape
{
public:
  Mesh(const std::vector<engine::Vertex>& vertices);
  void render() const override;
};


}  // namespace apeiron::opengl


#endif  // APEIRON_OPENGL_MESH_H

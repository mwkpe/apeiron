#ifndef APEIRON_OPENGL_MESH_H
#define APEIRON_OPENGL_MESH_H


#include <cstdint>
#include <vector>
#include "apeiron/opengl/vertex_array.h"


namespace apeiron::opengl {


class Mesh final : public Vertex_array
{
public:
  template<typename T> void init(const std::vector<T>& vertices,
      Usage_hint hint = Usage_hint::Static);
  template<typename T> void update(const std::vector<T>& vertices);

  void render() const override;
  void render_batched(std::uint32_t count) const;
  void render_points_batched(std::uint32_t count) const;
};


}  // namespace apeiron::opengl


#endif  // APEIRON_OPENGL_MESH_H

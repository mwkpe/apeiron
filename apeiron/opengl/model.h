#ifndef APEIRON_OPENGL_MODEL_H
#define APEIRON_OPENGL_MODEL_H


#include <cstddef>
#include <string_view>
#include <vector>
#include "apeiron/engine/vertex.h"
#include "apeiron/opengl/triangles.h"


namespace apeiron::opengl {


class Model
{
public:
  std::vector<Triangles>::const_iterator begin() const { return std::cbegin(meshes_); }
  std::vector<Triangles>::const_iterator end() const { return std::cend(meshes_); }
  template<typename T = engine::Vertex> void load(std::string_view filename);
  void render() const;
  void render(std::size_t index) const;

private:
  std::vector<Triangles> meshes_;
};


}  // namespace apeiron::opengl


#endif  // APEIRON_OPENGL_MODEL_H

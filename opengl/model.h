#ifndef APEIRON_OPENGL_MODEL_H
#define APEIRON_OPENGL_MODEL_H


#include <string_view>
#include <vector>
#include "opengl/mesh.h"


namespace apeiron::opengl {


class Model
{
public:
  std::vector<Mesh>::const_iterator begin() const { return std::cbegin(meshes_); }
  std::vector<Mesh>::const_iterator end() const { return std::cend(meshes_); }
  void load(std::string_view filename);

private:
  std::vector<Mesh> meshes_;
};


}  // namespace apeiron::opengl


#endif  // APEIRON_OPENGL_MODEL_H

#ifndef APEIRON_ENGINE_MODEL_LOADER_H
#define APEIRON_ENGINE_MODEL_LOADER_H


#include <cstdint>
#include <string>
#include <string_view>
#include <vector>
#include "apeiron/engine/vertex.h"


namespace apeiron::engine {


struct Material
{
  std::string diffuse_texture_filename;
};


template<typename T = Vertex> struct Mesh
{
  std::vector<T> vertices;
  std::int32_t material_index = -1;
};


template<typename T = Vertex> struct Model
{
  std::vector<Mesh<T>> meshes;
  std::vector<Material> materials;
};


template<typename T = Vertex> Model<T> load_model(std::string_view filename);


}  // namespace apeiron::engine


#endif  // APEIRON_ENGINE_MODEL_LOADER_H

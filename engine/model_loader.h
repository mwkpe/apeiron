#ifndef APEIRON_ENGINE_MODEL_LOADER_H
#define APEIRON_ENGINE_MODEL_LOADER_H


#include <string>
#include <string_view>
#include <vector>
#include "engine/vertex.h"


namespace apeiron::engine {


struct Material_data
{
  std::string diffuse_texture_filename;
};


template<typename T = Vertex> struct Mesh_data
{
  std::vector<T> vertices;
  int material_index = -1;
};


template<typename T = Vertex> struct Model_data
{
  std::vector<Mesh_data<T>> meshes;
  std::vector<Material_data> materials;
};


template<typename T = Vertex> Model_data<T> load_model(std::string_view filename);


}  // namespace apeiron::engine


#endif  // APEIRON_ENGINE_MODEL_LOADER_H

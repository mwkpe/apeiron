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


struct Mesh_data
{
  std::vector<Vertex> vertices;
  int material_index = -1;
};


struct Model_data
{
  std::vector<Mesh_data> meshes;
  std::vector<Material_data> materials;
};


Model_data load_model(std::string_view filename);


}  // namespace apeiron::engine


#endif  // APEIRON_ENGINE_MODEL_LOADER_H

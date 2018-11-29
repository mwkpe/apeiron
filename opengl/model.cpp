#include "model.h"


#include "engine/model_loader.h"


void apeiron::opengl::Model::load(std::string_view filename)
{
  auto model_data = engine::load_model(filename);
  for (const auto& mesh_data : model_data.meshes)
    meshes_.emplace_back(mesh_data.vertices);
}

#include "model.h"


#include "engine/model_loader.h"


void apeiron::opengl::Model::load(std::string_view filename)
{
  for (auto&& mesh : engine::load_model(filename))
    meshes_.emplace_back(std::move(mesh));
}

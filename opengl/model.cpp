#include "model.h"


#include "engine/vertex.h"
#include "engine/model_loader.h"


template<typename T> void apeiron::opengl::Model::load(std::string_view filename)
{
  auto model_data = engine::load_model<T>(filename);
  for (const auto& mesh_data : model_data.meshes)
    meshes_.emplace_back(mesh_data.vertices);
}


void apeiron::opengl::Model::render() const
{
  for (const auto& mesh : meshes_)
    mesh.render();
}


using namespace apeiron::engine;
using namespace apeiron::opengl;

template void Model::load<Vertex>(std::string_view);
template void Model::load<Vertex_simple>(std::string_view);
template void Model::load<Vertex_normal>(std::string_view);
template void Model::load<Vertex_color>(std::string_view);
template void Model::load<Vertex_texcoords>(std::string_view);
template void Model::load<Vertex_normal_color>(std::string_view);
template void Model::load<Vertex_normal_texcoords>(std::string_view);

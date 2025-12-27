#include "model.h"


#include "apeiron/engine/vertex.h"
#include "apeiron/engine/model_loader.h"


template<typename T> void apeiron::opengl::Model::load(std::string_view filename)
{
  auto model = engine::load_model<T>(filename);

  for (const auto& mesh : model.meshes) {
    meshes_.emplace_back(mesh.vertices);
  }
}


void apeiron::opengl::Model::render() const
{
  for (const auto& mesh : meshes_) {
    mesh.render();
  }
}


void apeiron::opengl::Model::render(std::size_t index) const
{
  if (index < meshes_.size()) {
    meshes_[index].render();
  }
}


namespace apeiron::opengl {


template void Model::load<apeiron::engine::Vertex>(std::string_view);
template void Model::load<apeiron::engine::Vertex_simple>(std::string_view);
template void Model::load<apeiron::engine::Vertex_normal>(std::string_view);
template void Model::load<apeiron::engine::Vertex_color>(std::string_view);
template void Model::load<apeiron::engine::Vertex_texcoords>(std::string_view);
template void Model::load<apeiron::engine::Vertex_normal_color>(std::string_view);
template void Model::load<apeiron::engine::Vertex_normal_texcoords>(std::string_view);


}  // namespace apeiron::opengl

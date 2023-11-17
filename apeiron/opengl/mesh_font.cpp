#include "mesh_font.h"


#include "apeiron/engine/vertex.h"
#include "apeiron/engine/model_loader.h"


template<typename T> void apeiron::opengl::Mesh_font::load(std::string_view filename,
    float letter_spacing, float letter_height, std::size_t ascii_offset)
{
  letter_spacing_ = letter_spacing;
  letter_height_ = letter_height;
  ascii_offset_ = ascii_offset;

  auto model_data = engine::load_model<T>(filename);
  for (const auto& mesh_data : model_data.meshes)
    meshes_.emplace_back(mesh_data.vertices);
}


void apeiron::opengl::Mesh_font::render(char c) const
{
  std::size_t index = c - ascii_offset_;
  if (index < meshes_.size())
    meshes_[index].render();
}


float apeiron::opengl::Mesh_font::letter_position(char c) const
{
  std::size_t index = c - ascii_offset_;
  return index * letter_spacing_;
}


template void apeiron::opengl::Mesh_font::load<apeiron::engine::Vertex>(std::string_view, float, float, std::size_t);
template void apeiron::opengl::Mesh_font::load<apeiron::engine::Vertex_simple>(std::string_view, float, float, std::size_t);
template void apeiron::opengl::Mesh_font::load<apeiron::engine::Vertex_normal>(std::string_view, float, float, std::size_t);
template void apeiron::opengl::Mesh_font::load<apeiron::engine::Vertex_color>(std::string_view, float, float, std::size_t);
template void apeiron::opengl::Mesh_font::load<apeiron::engine::Vertex_texcoords>(std::string_view, float, float, std::size_t);
template void apeiron::opengl::Mesh_font::load<apeiron::engine::Vertex_normal_color>(std::string_view, float, float, std::size_t);
template void apeiron::opengl::Mesh_font::load<apeiron::engine::Vertex_normal_texcoords>(std::string_view, float, float, std::size_t);

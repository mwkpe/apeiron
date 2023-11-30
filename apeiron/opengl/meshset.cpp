#include "meshset.h"


#include <algorithm>
#include <glad/glad.h>
#include "apeiron/engine/vertex.h"


template<typename T> void apeiron::opengl::Meshset::set_data(const std::vector<T>& vertices,
    Tile_data&& tile_data)
{
  set_buffers(vertices);
  tile_data_ = std::move(tile_data);
}


template<typename T> void apeiron::opengl::Meshset::set_data(const std::vector<T>& vertices,
    const Tile_data& tile_data)
{
  set_buffers(vertices);
  tile_data_ = tile_data;
}


void apeiron::opengl::Meshset::set_tile_spacing(const std::vector<glm::vec2>& tile_spacing)
{
  tile_spacing_ = tile_spacing;
}


void apeiron::opengl::Meshset::set_tile_spacing(std::vector<glm::vec2>&& tile_spacing)
{
  tile_spacing_ = std::move(tile_spacing);
}


bool apeiron::opengl::Meshset::empty(std::uint32_t index) const
{
  if (const std::uint32_t i = index - index_offset_; i < tile_data_.size())
    return std::get<1>(tile_data_[i]) == 0;

  return true;
}


glm::vec2 apeiron::opengl::Meshset::tile_spacing(std::uint32_t index) const
{
  if (const std::uint32_t i = index - index_offset_; i < tile_spacing_.size())
    return tile_spacing_[i];

  return tile_size_;
}


void apeiron::opengl::Meshset::render(std::uint32_t index) const
{
  index = std::min(index - index_offset_, static_cast<std::uint32_t>(tile_data_.size()) - 1);
  auto [tile_index, vertex_count] = tile_data_[index];
  glBindVertexArray(vao_);
  glDrawArrays(GL_TRIANGLES, static_cast<GLint>(tile_index), static_cast<GLsizei>(vertex_count));
}


template void apeiron::opengl::Meshset::set_data(const std::vector<apeiron::engine::Vertex>&, 
    apeiron::opengl::Meshset::Tile_data&&);
template void apeiron::opengl::Meshset::set_data(const std::vector<apeiron::engine::Vertex>&, 
    const apeiron::opengl::Meshset::Tile_data&);

template void apeiron::opengl::Meshset::set_data(const std::vector<apeiron::engine::Vertex_color>&, 
    apeiron::opengl::Meshset::Tile_data&&);
template void apeiron::opengl::Meshset::set_data(const std::vector<apeiron::engine::Vertex_color>&, 
    const apeiron::opengl::Meshset::Tile_data&);

template void apeiron::opengl::Meshset::set_data(
    const std::vector<apeiron::engine::Vertex_normal_color>&, 
    apeiron::opengl::Meshset::Tile_data&&);
template void apeiron::opengl::Meshset::set_data(
    const std::vector<apeiron::engine::Vertex_normal_color>&, 
    const apeiron::opengl::Meshset::Tile_data&);

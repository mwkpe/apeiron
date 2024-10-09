#include "meshset.h"


#include <algorithm>
#include <glad/glad.h>
#include "apeiron/engine/vertex.h"


template<typename T> void apeiron::opengl::Meshset::set_data(const std::vector<T>& vertices,
    Index_vector&& indices)
{
  set_buffers(vertices);
  indices_ = std::move(indices);
}


template<typename T> void apeiron::opengl::Meshset::set_data(const std::vector<T>& vertices,
    const Index_vector& indices)
{
  set_buffers(vertices);
  indices_ = indices;
}


void apeiron::opengl::Meshset::set_tile_spacing(const std::vector<glm::vec2>& tile_spacing)
{
  tile_spacing_ = tile_spacing;
}


void apeiron::opengl::Meshset::set_tile_spacing(std::vector<glm::vec2>&& tile_spacing)
{
  tile_spacing_ = std::move(tile_spacing);
}


bool apeiron::opengl::Meshset::tile_empty(std::uint32_t index) const
{
  if (const std::uint32_t i = index - index_offset_; i < indices_.size()) {
    return std::get<1>(indices_[i]) == 0;
  }

  return true;
}


auto apeiron::opengl::Meshset::tile_data(std::uint32_t index) const
    -> std::tuple<std::uint32_t, std::uint32_t>
{
  if (const std::uint32_t i = index - index_offset_; i < indices_.size()) {
    return indices_[i];
  }

  return {0, 0};
}


glm::vec2 apeiron::opengl::Meshset::tile_spacing(std::uint32_t index) const
{
  if (const std::uint32_t i = index - index_offset_; i < tile_spacing_.size()) {
    return tile_spacing_[i];
  }

  return tile_size_;
}


void apeiron::opengl::Meshset::render(std::uint32_t index) const
{
  index = std::min(index - index_offset_, static_cast<std::uint32_t>(indices_.size()) - 1);
  auto [tile_index, vertex_count] = indices_[index];
  glBindVertexArray(vao_);
  glDrawArrays(GL_TRIANGLES, static_cast<GLint>(tile_index), static_cast<GLsizei>(vertex_count));
}


void apeiron::opengl::Meshset::render_batched(std::uint32_t count) const
{
  glBindVertexArray(vao_);
  glMultiDrawArraysIndirect(GL_TRIANGLES, nullptr, static_cast<GLint>(count), 0);
}


void apeiron::opengl::Meshset::render_points(std::uint32_t index) const
{
  index = std::min(index - index_offset_, static_cast<std::uint32_t>(indices_.size()) - 1);
  auto [tile_index, vertex_count] = indices_[index];
  glBindVertexArray(vao_);
  glDrawArrays(GL_POINTS, static_cast<GLint>(tile_index), static_cast<GLsizei>(vertex_count));
}


void apeiron::opengl::Meshset::render_points_batched(std::uint32_t count) const
{
  glBindVertexArray(vao_);
  glMultiDrawArraysIndirect(GL_POINTS, 0, static_cast<GLint>(count), 0);
}


template void apeiron::opengl::Meshset::set_data(const std::vector<apeiron::engine::Vertex>&, 
    apeiron::opengl::Meshset::Index_vector&&);
template void apeiron::opengl::Meshset::set_data(const std::vector<apeiron::engine::Vertex>&, 
    const apeiron::opengl::Meshset::Index_vector&);

template void apeiron::opengl::Meshset::set_data(const std::vector<apeiron::engine::Vertex_simple>&, 
    apeiron::opengl::Meshset::Index_vector&&);
template void apeiron::opengl::Meshset::set_data(const std::vector<apeiron::engine::Vertex_simple>&, 
    const apeiron::opengl::Meshset::Index_vector&);

template void apeiron::opengl::Meshset::set_data(const std::vector<apeiron::engine::Vertex_color>&, 
    apeiron::opengl::Meshset::Index_vector&&);
template void apeiron::opengl::Meshset::set_data(const std::vector<apeiron::engine::Vertex_color>&, 
    const apeiron::opengl::Meshset::Index_vector&);

template void apeiron::opengl::Meshset::set_data(
    const std::vector<apeiron::engine::Vertex_normal_color>&, 
    apeiron::opengl::Meshset::Index_vector&&);
template void apeiron::opengl::Meshset::set_data(
    const std::vector<apeiron::engine::Vertex_normal_color>&, 
    const apeiron::opengl::Meshset::Index_vector&);

template void apeiron::opengl::Meshset::set_data(const std::vector<apeiron::engine::Vertex_index>&,
    apeiron::opengl::Meshset::Index_vector&&);
template void apeiron::opengl::Meshset::set_data(const std::vector<apeiron::engine::Vertex_index>&,
    const apeiron::opengl::Meshset::Index_vector&);

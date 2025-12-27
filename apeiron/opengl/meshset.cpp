#include "meshset.h"


#include <algorithm>
#include <glad/glad.h>
#include "apeiron/engine/vertex.h"


template<typename T> void apeiron::opengl::Meshset::set_data(const std::vector<T>& vertices,
    std::vector<Meshset_entry>&& entries, Usage_hint hint)
{
  vertex_count_ = vertices.size();
  entries_ = std::move(entries);
  set_buffers(vertices, hint);
}


template<typename T> void apeiron::opengl::Meshset::set_data(const std::vector<T>& vertices,
    const std::vector<Meshset_entry>& entries, Usage_hint hint)
{
  vertex_count_ = vertices.size();
  entries_ = entries;
  set_buffers(vertices, hint);
}


template<typename T> void apeiron::opengl::Meshset::update_data(const std::vector<T>& vertices,
    std::vector<Meshset_entry>&& entries)
{
  vertex_count_ = vertices.size();
  entries_ = std::move(entries);
  update_buffers(vertices);
}


template<typename T> void apeiron::opengl::Meshset::update_data(const std::vector<T>& vertices,
    const std::vector<Meshset_entry>& entries)
{
  vertex_count_ = vertices.size();
  entries_ = entries;
  update_buffers(vertices);
}


bool apeiron::opengl::Meshset::is_empty(std::uint32_t index) const
{
  if (auto entry = entry_at(index); entry) {
    return entry->vertex_count == 0;
  }

  return true;
}


auto apeiron::opengl::Meshset::entry_at(std::uint32_t index) const -> std::optional<Meshset_entry>
{
  if (index < index_offset_) {
    return std::nullopt;
  }

  if (const std::uint32_t i = index - index_offset_; i < entries_.size()) {
    return entries_[i];
  }

  return std::nullopt;
}


void apeiron::opengl::Meshset::render() const
{
  glBindVertexArray(vao_);
  glDrawArrays(GL_TRIANGLES, 0, static_cast<GLsizei>(vertex_count_));
}


void apeiron::opengl::Meshset::render(std::uint32_t index) const
{
  if (auto entry = entry_at(index); entry) {
    glBindVertexArray(vao_);
    glDrawArrays(GL_TRIANGLES, static_cast<GLint>(entry->first_vertex),
        static_cast<GLsizei>(entry->vertex_count));
  }
}


void apeiron::opengl::Meshset::render_batched(std::uint32_t count) const
{
  glBindVertexArray(vao_);
  glMultiDrawArraysIndirect(GL_TRIANGLES, nullptr, static_cast<GLint>(count), 0);
}


void apeiron::opengl::Meshset::render_points(std::uint32_t index) const
{
  if (auto entry = entry_at(index); entry) {
    glBindVertexArray(vao_);
    glDrawArrays(GL_POINTS, static_cast<GLint>(entry->first_vertex),
        static_cast<GLsizei>(entry->vertex_count));
  }
}


void apeiron::opengl::Meshset::render_points_batched(std::uint32_t count) const
{
  glBindVertexArray(vao_);
  glMultiDrawArraysIndirect(GL_POINTS, 0, static_cast<GLint>(count), 0);
}


using apeiron::engine::Vertex;
using apeiron::engine::Vertex_simple;
using apeiron::engine::Vertex_normal;
using apeiron::engine::Vertex_color;
using apeiron::engine::Vertex_texcoords;
using apeiron::engine::Vertex_normal_color;
using apeiron::engine::Vertex_normal_texcoords;
using apeiron::engine::Vertex_index;
using apeiron::opengl::Usage_hint;


namespace apeiron::opengl {


template void Meshset::set_data(const std::vector<Vertex>&, std::vector<Meshset_entry>&&, Usage_hint);
template void Meshset::set_data(const std::vector<Vertex_simple>&, std::vector<Meshset_entry>&&, Usage_hint);
template void Meshset::set_data(const std::vector<Vertex_color>&, std::vector<Meshset_entry>&&, Usage_hint);
template void Meshset::set_data(const std::vector<Vertex_normal>&, std::vector<Meshset_entry>&&, Usage_hint);
template void Meshset::set_data(const std::vector<Vertex_texcoords>&, std::vector<Meshset_entry>&&, Usage_hint);
template void Meshset::set_data(const std::vector<Vertex_normal_color>&, std::vector<Meshset_entry>&&, Usage_hint);
template void Meshset::set_data(const std::vector<Vertex_normal_texcoords>&, std::vector<Meshset_entry>&&, Usage_hint);
template void Meshset::set_data(const std::vector<Vertex_index>&, std::vector<Meshset_entry>&&, Usage_hint);

template void Meshset::set_data(const std::vector<Vertex>&, const std::vector<Meshset_entry>&, Usage_hint);
template void Meshset::set_data(const std::vector<Vertex_simple>&, const std::vector<Meshset_entry>&, Usage_hint);
template void Meshset::set_data(const std::vector<Vertex_normal>&, const std::vector<Meshset_entry>&, Usage_hint);
template void Meshset::set_data(const std::vector<Vertex_color>&, const std::vector<Meshset_entry>&, Usage_hint);
template void Meshset::set_data(const std::vector<Vertex_texcoords>&, const std::vector<Meshset_entry>&, Usage_hint);
template void Meshset::set_data(const std::vector<Vertex_normal_color>&, const std::vector<Meshset_entry>&, Usage_hint);
template void Meshset::set_data(const std::vector<Vertex_normal_texcoords>&, const std::vector<Meshset_entry>&, Usage_hint);
template void Meshset::set_data(const std::vector<Vertex_index>&, const std::vector<Meshset_entry>&, Usage_hint);

template void Meshset::update_data(const std::vector<Vertex>&, std::vector<Meshset_entry>&&);
template void Meshset::update_data(const std::vector<Vertex_simple>&, std::vector<Meshset_entry>&&);
template void Meshset::update_data(const std::vector<Vertex_normal>&, std::vector<Meshset_entry>&&);
template void Meshset::update_data(const std::vector<Vertex_color>&, std::vector<Meshset_entry>&&);
template void Meshset::update_data(const std::vector<Vertex_texcoords>&, std::vector<Meshset_entry>&&);
template void Meshset::update_data(const std::vector<Vertex_normal_color>&, std::vector<Meshset_entry>&&);
template void Meshset::update_data(const std::vector<Vertex_normal_texcoords>&, std::vector<Meshset_entry>&&);
template void Meshset::update_data(const std::vector<Vertex_index>&, std::vector<Meshset_entry>&&);

template void Meshset::update_data(const std::vector<Vertex>&, const std::vector<Meshset_entry>&);
template void Meshset::update_data(const std::vector<Vertex_simple>&, const std::vector<Meshset_entry>&);
template void Meshset::update_data(const std::vector<Vertex_normal>&, const std::vector<Meshset_entry>&);
template void Meshset::update_data(const std::vector<Vertex_color>&, const std::vector<Meshset_entry>&);
template void Meshset::update_data(const std::vector<Vertex_texcoords>&, const std::vector<Meshset_entry>&);
template void Meshset::update_data(const std::vector<Vertex_normal_color>&, const std::vector<Meshset_entry>&);
template void Meshset::update_data(const std::vector<Vertex_normal_texcoords>&, const std::vector<Meshset_entry>&);
template void Meshset::update_data(const std::vector<Vertex_index>&, const std::vector<Meshset_entry>&);


}  // namespace apeiron::opengl

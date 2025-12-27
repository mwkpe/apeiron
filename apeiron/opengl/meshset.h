#ifndef APEIRON_OPENGL_MESHSET_H
#define APEIRON_OPENGL_MESHSET_H


#include <cstdint>
#include <optional>
#include <vector>
#include <glm/glm.hpp>
#include "apeiron/opengl/vertex_array.h"


namespace apeiron::opengl {


struct Meshset_entry
{
  std::uint32_t first_vertex;
  std::uint32_t vertex_count;
  glm::vec3 size;
};


class Meshset final : public Vertex_array
{
public:
  template<typename T> void set_data(const std::vector<T>& vertices,
      std::vector<Meshset_entry>&& entries, Usage_hint hint = Usage_hint::Static);
  template<typename T> void set_data(const std::vector<T>& vertices,
      const std::vector<Meshset_entry>& entries, Usage_hint hint = Usage_hint::Static);

  template<typename T> void update_data(const std::vector<T>& vertices,
      std::vector<Meshset_entry>&& entries);
  template<typename T> void update_data(const std::vector<T>& vertices,
      const std::vector<Meshset_entry>& entries);

  void set_index_offset(std::uint32_t offset) { index_offset_ = offset; }

  void render() const override;
  void render(std::uint32_t index) const override;
  void render_batched(std::uint32_t count) const;
  void render_points(std::uint32_t index) const;
  void render_points_batched(std::uint32_t count) const;

  [[nodiscard]] bool is_empty() const { return entries_.empty(); }
  [[nodiscard]] bool is_empty(std::uint32_t index) const;
  [[nodiscard]] std::uint32_t entry_count() const { return entries_.size(); }
  [[nodiscard]] std::optional<Meshset_entry> entry_at(std::uint32_t index) const;

private:
  std::vector<Meshset_entry> entries_;
  std::uint32_t vertex_count_ = 0;
  std::uint32_t index_offset_ = 0;
};


}  // namespace apeiron::opengl


#endif  // APEIRON_OPENGL_MESHSET_H

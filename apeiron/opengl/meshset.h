#ifndef APEIRON_OPENGL_MESHSET_H
#define APEIRON_OPENGL_MESHSET_H


#include <cstdint>
#include <tuple>
#include <vector>
#include <glm/glm.hpp>
#include "apeiron/opengl/shape.h"


namespace apeiron::opengl {


class Meshset final : public Shape
{
public:
  using Index_vector = std::vector<std::tuple<std::uint32_t, std::uint32_t>>;

  Meshset() = default;

  template<typename T> void set_data(const std::vector<T>& vertices, Index_vector&& indices);
  template<typename T> void set_data(const std::vector<T>& vertices, const Index_vector& indices);

  void set_tile_size(const glm::vec2& tile_size) { tile_size_ = tile_size; }
  void set_tile_spacing(const std::vector<glm::vec2>& tile_spacing);
  void set_tile_spacing(std::vector<glm::vec2>&& tile_spacing);
  void set_index_offset(std::uint32_t offset) { index_offset_ = offset; }

  void render(std::uint32_t index) const override;
  void render_batched(std::uint32_t count) const;
  void render_points(std::uint32_t index) const;
  void render_points_batched(std::uint32_t count) const;

  [[nodiscard]] std::uint32_t tile_count() const { return indices_.size(); }
  [[nodiscard]] bool tile_empty(std::uint32_t index) const;
  [[nodiscard]] std::tuple<std::uint32_t, std::uint32_t> tile_data(std::uint32_t index) const;
  [[nodiscard]] glm::vec2 tile_size() const { return tile_size_; }
  [[nodiscard]] glm::vec2 tile_spacing(std::uint32_t index) const;

private:
  Index_vector indices_;
  std::vector<glm::vec2> tile_spacing_;
  std::uint32_t index_offset_ = 0;
  glm::vec2 tile_size_ = glm::vec2{1.0f};
};


}  // namespace apeiron::opengl


#endif  // APEIRON_OPENGL_MESHSET_H

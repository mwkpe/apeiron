#ifndef APEIRON_OPENGL_MESHSET_H
#define APEIRON_OPENGL_MESHSET_H


#include <cstdint>
#include <string_view>
#include <tuple>
#include <vector>
#include <glm/glm.hpp>
#include "opengl/shape.h"


namespace apeiron::opengl {


class Meshset final : public Shape
{
public:
  using Spacing_vector = std::vector<std::tuple<float, float>>;

  Meshset() = default;
  void load_from_image(std::string_view filename, std::uint32_t rows, std::uint32_t cols,
      std::uint32_t index_offset = 0, float tile_width = 1.0f, float tile_height = 1.0f,
      bool optimize = true);
  template<typename T> void set_data(const std::vector<T>& vertices,
      std::vector<std::uint32_t>&& tile_indices,
      std::vector<std::uint32_t>&& vertex_counts);
  template<typename T> void set_data(const std::vector<T>& vertices,
      const std::vector<std::uint32_t>& tile_indices,
      const std::vector<std::uint32_t>& vertex_counts);
  void set_tile_spacing(const Spacing_vector& tile_spacing);
  void set_tile_spacing(Spacing_vector&& tile_spacing);
  void set_index_offset(std::uint32_t offset) { index_offset_ = offset; }
  void render(std::uint32_t index) const;
  std::uint32_t tile_count() const { return tile_indices_.size(); }
  bool empty(std::uint32_t index) const;
  glm::vec2 tile_size() const { return glm::vec2{tile_width_, tile_height_}; }
  float tile_width() const { return tile_width_; }
  float tile_height() const { return tile_height_; }
  std::tuple<float, float> tile_spacing(std::uint32_t index) const;

private:
  std::vector<std::uint32_t> tile_indices_;
  std::vector<std::uint32_t> vertex_counts_;
  Spacing_vector tile_spacing_;
  std::uint32_t tile_count_ = 1;
  std::uint32_t index_offset_ = 0;
  float tile_width_ = 1.0f;
  float tile_height_ = 1.0f;
};


}  // namespace apeiron::opengl


#endif  // APEIRON_OPENGL_MESHSET_H

#ifndef APEIRON_FRAME_BUFFER_H
#define APEIRON_FRAME_BUFFER_H


#include <cstdint>
#include "apeiron/opengl/enums.h"


namespace apeiron::opengl {


class Frame_buffer
{
public:
  Frame_buffer() = default;
  ~Frame_buffer();
  Frame_buffer(const Frame_buffer&) = delete;
  Frame_buffer(Frame_buffer&&) noexcept;
  Frame_buffer& operator=(const Frame_buffer&) = delete;
  Frame_buffer& operator=(Frame_buffer&&) noexcept;

  void init(std::int32_t width, std::int32_t height, std::int32_t samples = 1,
      Texture_filter filter = Texture_filter::Linear);
  void init_depth_buffer(std::int32_t width, std::int32_t height);
  void init_depth_buffer_cube(std::int32_t width, std::int32_t height);

  void bind() const;
  void unbind() const;
  void bind_texture() const;
  void bind_depth_texture() const;
  void bind_depth_texture_cube() const;
  void unbind_texture() const;
  void blit() const;

  [[nodiscard]] std::uint32_t texture_id() const { return color_buffer_id_; }
  [[nodiscard]] std::uint32_t depth_buffer_id() const { return depth_buffer_id_; }

private:
  void delete_buffers();

  std::int32_t width_ = 0;
  std::int32_t height_ = 0;
  std::uint32_t frame_buffer_render_id_ = 0;
  std::uint32_t frame_buffer_resolve_id_ = 0;
  std::uint32_t sample_buffer_id_ = 0;
  std::uint32_t color_buffer_id_ = 0;
  std::uint32_t depth_buffer_id_ = 0;
  std::uint32_t render_buffer_id_ = 0;
};


}  // namespace apeiron::opengl


#endif  // APEIRON_FRAME_BUFFER_H
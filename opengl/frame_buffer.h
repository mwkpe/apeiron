#ifndef APEIRON_FRAME_BUFFER_H
#define APEIRON_FRAME_BUFFER_H


#include <cstdint>


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
  void init(std::int32_t width, std::int32_t height, bool depth_texture = false,
      std::int32_t samples = 1);
  void bind() const;
  void unbind() const;
  void bind_texture() const;
  void unbind_texture() const;
  void blit() const;
  std::uint32_t texture_id() const { return color_buffer_id_; }
  std::uint32_t depth_buffer_id() const { return depth_buffer_id_; }

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
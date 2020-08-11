#ifndef APEIRON_OPENGL_TEXTURE_H
#define APEIRON_OPENGL_TEXTURE_H


#include <cstdint>
#include <string_view>


namespace apeiron {


enum class Texture_filter { Linear, Nearest };
enum class Wrap_mode { Clamp_to_edge, Repeat };
enum class Pixel_format { Rgb, Rgba, Bgr, Bgra };


}  // apeiron


namespace apeiron::opengl {


class Texture
{
public:
  Texture() = default;
  ~Texture();
  Texture(const Texture&) = delete;
  Texture(Texture&&) noexcept;
  Texture& operator=(const Texture&) = delete;
  Texture& operator=(Texture&&) noexcept;
  void set_filter(Texture_filter min, Texture_filter mag);
  void set_wrap(Wrap_mode s, Wrap_mode t);
  void load(std::string_view filename, Pixel_format pixel_format);
  void create(const std::uint8_t* pixel, int width, int height, Pixel_format pixel_format);
  void update(const std::uint8_t* pixel, int width, int height, Pixel_format pixel_format);
  void bind() const;
  std::uint32_t id() const { return id_; }

private:
  std::uint32_t id_ = 0;
  int anisotropy_level = 1;
  bool generate_mipmap = false;
  Texture_filter min_filter_ = Texture_filter::Linear;
  Texture_filter mag_filter_ = Texture_filter::Linear;
  Wrap_mode wrap_mode_s_ = Wrap_mode::Clamp_to_edge;
  Wrap_mode wrap_mode_t_ = Wrap_mode::Clamp_to_edge;
};


}  // namespace apeiron::opengl


#endif  // APEIRON_OPENGL_TEXTURE_H

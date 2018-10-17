#ifndef APEIRON_OPENGL_TEXTURE_H
#define APEIRON_OPENGL_TEXTURE_H


#include <cstdint>
#include <string_view>


namespace apeiron::opengl {


enum class Texture_filter { Linear, Nearest };
enum class Wrap_mode { Clamp_to_edge, Repeat };


class Texture
{
public:
  Texture() = default;
  ~Texture();
  Texture(const Texture&) = delete;
  Texture(Texture&&);
  Texture& operator=(const Texture&) = delete;
  Texture& operator=(Texture&&);
  void load(std::string_view filename,
      Texture_filter min_filter = Texture_filter::Linear,
      Texture_filter mag_filter = Texture_filter::Linear,
      std::uint32_t anisotropy_level = 1,
      Wrap_mode wrap_s = Wrap_mode::Clamp_to_edge,
      Wrap_mode wrap_t = Wrap_mode::Clamp_to_edge);
  void bind() const;
  std::uint32_t id() const { return id_; }

private:
  std::uint32_t id_ = 0;
};


}  // namespace apeiron::opengl


#endif  // APEIRON_OPENGL_TEXTURE_H

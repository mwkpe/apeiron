#ifndef APEIRON_OPENGL_TEXTURE_H
#define APEIRON_OPENGL_TEXTURE_H


#include <cstdint>
#include <string_view>


namespace apeiron::opengl {


class Texture
{
public:
  Texture() = default;
  ~Texture();
  Texture(const Texture&) = delete;
  Texture(Texture&&) = delete;
  Texture& operator=(const Texture&) = delete;
  Texture& operator=(Texture&&) = delete;
  void load(std::string_view filename);
  void bind() const;
  std::uint32_t id() const { return id_; }

private:
  std::uint32_t id_ = 0;
};


}  // namespace apeiron::opengl


#endif  // APEIRON_OPENGL_TEXTURE_H

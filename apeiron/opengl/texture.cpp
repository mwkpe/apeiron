#include "texture.h"


#include <glad/glad.h>
#include "apeiron/engine/error.h"
#include "apeiron/engine/image_loader.h"


apeiron::opengl::Texture::Texture(Texture&& other) noexcept
{
  id_ = other.id_;
  other.id_ = 0;

  anisotropy_level_ = other.anisotropy_level_;
  generate_mipmap_ = other.generate_mipmap_;
  min_filter_ = other.min_filter_;
  mag_filter_ = other.mag_filter_;
  wrap_mode_s_ = other.wrap_mode_s_;
  wrap_mode_t_ = other.wrap_mode_t_;
}


auto apeiron::opengl::Texture::operator=(Texture&& other) noexcept -> Texture&
{
  if (&other == this) {
    return *this;
  }

  if (id_ > 0) {
    glDeleteTextures(1, &id_);
  }

  id_ = other.id_;
  other.id_ = 0;

  anisotropy_level_ = other.anisotropy_level_;
  generate_mipmap_ = other.generate_mipmap_;
  min_filter_ = other.min_filter_;
  mag_filter_ = other.mag_filter_;
  wrap_mode_s_ = other.wrap_mode_s_;
  wrap_mode_t_ = other.wrap_mode_t_;

  return *this;
}


apeiron::opengl::Texture::~Texture()
{
  if (id_ > 0) {
    glDeleteTextures(1, &id_);
  }
}


void apeiron::opengl::Texture::set_filter(Texture_filter min, Texture_filter mag)
{
  min_filter_ = min;
  mag_filter_ = mag;
}


void apeiron::opengl::Texture::set_wrap(Wrap_mode s, Wrap_mode t)
{
  wrap_mode_s_ = s;
  wrap_mode_t_ = t;
}


void apeiron::opengl::Texture::load(std::string_view filename, Pixel_format pixel_format)
{
  auto&& [pixel, width, height, channel_count] = engine::load_image(filename);

  switch (pixel_format) {
    case Pixel_format::Rgb:
    [[fallthrough]];
    case Pixel_format::Bgr:
      if (channel_count != 3) {
        throw engine::Error{"Image format error"};
      }
    break;
    case Pixel_format::Rgba:
    [[fallthrough]];
    case Pixel_format::Bgra:
      if (channel_count != 4) {
        throw engine::Error{"Image format error"};
      }
    break;
  }

  create(pixel.data(), width, height, pixel_format);
}


void apeiron::opengl::Texture::create(const std::uint8_t* pixel,
    int width, int height, Pixel_format pixel_format)
{
  if (id_ > 0) {
    glDeleteTextures(1, &id_);
    id_ = 0;
  }

  glGenTextures(1, &id_);
  glBindTexture(GL_TEXTURE_2D, id_);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, as_gl(wrap_mode_s_));
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, as_gl(wrap_mode_t_));
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, as_gl(min_filter_));
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, as_gl(mag_filter_));

  if (anisotropy_level_ > 1) {
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, anisotropy_level_);
  }

  if (unpack_alignment_ != 4) {
    glPixelStorei(GL_UNPACK_ALIGNMENT, unpack_alignment_);
  }

  switch (pixel_format) {
    case Pixel_format::Rgb:
    [[fallthrough]];
    case Pixel_format::Bgr:
      glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB8, width, height, 0,
          as_gl(pixel_format), GL_UNSIGNED_BYTE, pixel);
    break;
    case Pixel_format::Rgba:
    [[fallthrough]];
    case Pixel_format::Bgra:
      glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0,
          as_gl(pixel_format), GL_UNSIGNED_BYTE, pixel);
    break;
  }

  glPixelStorei(GL_UNPACK_ALIGNMENT, 4);  // Set back to default

  if (generate_mipmap_) {
    glGenerateMipmap(GL_TEXTURE_2D);
  }
}


void apeiron::opengl::Texture::update(const std::uint8_t* pixel, int width, int height,
    Pixel_format pixel_format) const
{
  glBindTexture(GL_TEXTURE_2D, id_);

  if (unpack_alignment_ != 4) {
    glPixelStorei(GL_UNPACK_ALIGNMENT, unpack_alignment_);
  }

  glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, width, height,
      as_gl(pixel_format), GL_UNSIGNED_BYTE, pixel);
  glPixelStorei(GL_UNPACK_ALIGNMENT, 4);  // Set back to default
}


void apeiron::opengl::Texture::bind() const
{
  glBindTexture(GL_TEXTURE_2D, id_);
}

#include "texture.h"


#include "GL/glew.h"
#include "engine/error.h"
#include "engine/image_loader.h"


namespace {


GLenum translate(apeiron::Texture_filter texture_filter)
{
  switch (texture_filter) {
    case apeiron::Texture_filter::Nearest: return GL_NEAREST;
    case apeiron::Texture_filter::Linear:
    [[fallthrough]];
    default:
      return GL_LINEAR;
  }
}


GLenum translate(apeiron::Wrap_mode wrap_mode)
{
  switch (wrap_mode) {
    case apeiron::Wrap_mode::Repeat: return GL_REPEAT;
    case apeiron::Wrap_mode::Clamp_to_edge:
    [[fallthrough]];
    default:
      return GL_CLAMP_TO_EDGE;
  }
}


GLenum translate(apeiron::Pixel_format pixel_format)
{
  switch (pixel_format) {
    case apeiron::Pixel_format::Rgb: return GL_RGB;
    case apeiron::Pixel_format::Rgba: return GL_RGBA;
    case apeiron::Pixel_format::Bgr: return GL_BGR;
    case apeiron::Pixel_format::Bgra: return GL_BGRA;
  }

  return 0;
}


}  // namespace


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
  if (&other == this)
    return *this;

  if (id_ > 0)
    glDeleteTextures(1, &id_);

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
  if (id_ > 0)
    glDeleteTextures(1, &id_);
}


void apeiron::opengl::Texture::load(std::string_view filename, Pixel_format pixel_format)
{
  auto&& [pixel, width, height, channel_count] = engine::load_image(filename);

  switch (pixel_format) {
    case Pixel_format::Rgb:
    [[fallthrough]];
    case Pixel_format::Bgr:
      if (channel_count != 3)
        throw engine::Error{"Image format error"};
    break;
    case Pixel_format::Rgba:
    [[fallthrough]];
    case Pixel_format::Bgra:
      if (channel_count != 4)
        throw engine::Error{"Image format error"};
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

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, translate(wrap_mode_s_));
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, translate(wrap_mode_t_));
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, translate(min_filter_));
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, translate(mag_filter_));

  if (anisotropy_level_ > 1)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, anisotropy_level_);

  switch (pixel_format) {
    case Pixel_format::Rgb:
    [[fallthrough]];
    case Pixel_format::Bgr:
      glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB8, width, height, 0,
          translate(pixel_format), GL_UNSIGNED_BYTE, pixel);
    break;
    case Pixel_format::Rgba:
    [[fallthrough]];
    case Pixel_format::Bgra:
      glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0,
          translate(pixel_format), GL_UNSIGNED_BYTE, pixel);
    break;
  }

  if (generate_mipmap_)
    glGenerateMipmap(GL_TEXTURE_2D);
}


void apeiron::opengl::Texture::update(const std::uint8_t* pixel, int width, int height, Pixel_format pixel_format)
{
  glBindTexture(GL_TEXTURE_2D, id_);
  glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, width, height,
      translate(pixel_format), GL_UNSIGNED_BYTE, pixel);
}


void apeiron::opengl::Texture::bind() const
{
  glBindTexture(GL_TEXTURE_2D, id_);
}

#include "texture.h"


#include <vector>
#include "GL/glew.h"
#include "engine/error.h"
#include "engine/image_loader.h"


apeiron::opengl::Texture::Texture(Texture&& other) noexcept
{
  id_ = other.id_;
  other.id_ = 0;
}


auto apeiron::opengl::Texture::operator=(Texture&& other) noexcept -> Texture&
{
  if (&other == this)
    return *this;

  if (id_ > 0)
    glDeleteTextures(1, &id_);

  id_ = other.id_;
  other.id_ = 0;

  return *this;
}


apeiron::opengl::Texture::~Texture()
{
  if (id_ > 0)
    glDeleteTextures(1, &id_);
}


void apeiron::opengl::Texture::load(std::string_view filename,
    Texture_filter min_filter,
    Texture_filter mag_filter,
    std::uint32_t anisotropy_level,
    Wrap_mode wrap_s,
    Wrap_mode wrap_t)
{
  if (id_ > 0) {
    glDeleteTextures(1, &id_);
    id_ = 0;
  }

  auto&& [pixel, width, height, channel_count] = engine::load_image(filename);

  if (channel_count != 3 && channel_count != 4)
    throw engine::Error{"Image format not supported"};

  glGenTextures(1, &id_);
  glBindTexture(GL_TEXTURE_2D, id_);

  GLint gl_wrap_s;
  GLint gl_wrap_t;
  switch (wrap_s) {
    case Wrap_mode::Repeat:
      gl_wrap_s = GL_REPEAT;
      break;
    case Wrap_mode::Clamp_to_edge:
    [[fallthrough]];
    default:
      gl_wrap_s = GL_CLAMP_TO_EDGE;
  }
  switch (wrap_t) {
    case Wrap_mode::Repeat:
      gl_wrap_t = GL_REPEAT;
      break;
    case Wrap_mode::Clamp_to_edge:
    [[fallthrough]];
    default:
      gl_wrap_t = GL_CLAMP_TO_EDGE;
  }

  GLint gl_min_filter;
  GLint gl_mag_filter;
  switch (min_filter) {
    case Texture_filter::Nearest:
      gl_min_filter = GL_NEAREST;
      break;
    case Texture_filter::Linear:
    [[fallthrough]];
    default:
      gl_min_filter = GL_LINEAR;
  }
  switch (mag_filter) {
    case Texture_filter::Nearest:
      gl_mag_filter = GL_NEAREST;
      break;
    case Texture_filter::Linear:
    [[fallthrough]];
    default:
      gl_mag_filter = GL_LINEAR;
  }

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, gl_wrap_s);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, gl_wrap_t);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, gl_min_filter);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, gl_mag_filter);

  if (anisotropy_level > 1)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, anisotropy_level);

  switch (channel_count) {
    case 3:
      glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB8, width, height, 0,
          GL_RGB, GL_UNSIGNED_BYTE, pixel.data());
      break;
    case 4:
      glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0,
          GL_RGBA, GL_UNSIGNED_BYTE, pixel.data());
      break;
  }

  glGenerateMipmap(GL_TEXTURE_2D);
}


void apeiron::opengl::Texture::bind() const
{
  glBindTexture(GL_TEXTURE_2D, id_);
}

#include "enums.h"


#include <glad/glad.h>


std::int32_t apeiron::opengl::as_gl(Texture_filter texture_filter)
{
  switch (texture_filter) {
    case Texture_filter::Nearest: return GL_NEAREST;
    case Texture_filter::Linear: return GL_LINEAR;
  }

  return GL_LINEAR;
}


std::int32_t apeiron::opengl::as_gl(Wrap_mode wrap_mode)
{
  switch (wrap_mode) {
    case Wrap_mode::Repeat: return GL_REPEAT;
    case Wrap_mode::Clamp_to_edge: return GL_CLAMP_TO_EDGE;
  }

  return GL_CLAMP_TO_EDGE;
}


std::int32_t apeiron::opengl::as_gl(Pixel_format pixel_format)
{
  switch (pixel_format) {
    case Pixel_format::Rgb: return GL_RGB;
    case Pixel_format::Rgba: return GL_RGBA;
    case Pixel_format::Bgr: return GL_BGR;
    case Pixel_format::Bgra: return GL_BGRA;
  }

  return 0;
}


std::uint32_t apeiron::opengl::as_gl(Usage_hint hint)
{
  switch (hint) {
    case Usage_hint::Static: return GL_STATIC_DRAW;
    case Usage_hint::Dynamic: return GL_DYNAMIC_DRAW;
    case Usage_hint::Stream: return GL_STREAM_DRAW;
  }

  return GL_STATIC_DRAW;
}

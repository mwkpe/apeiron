#ifndef APEIRON_OPENGL_ENUMS_H
#define APEIRON_OPENGL_ENUMS_H


#include <cstdint>


namespace apeiron::opengl {


enum class Texture_filter { Linear, Nearest };
enum class Wrap_mode { Clamp_to_edge, Repeat };
enum class Pixel_format { Rgb, Rgba, Bgr, Bgra };
enum class Usage_hint { Static, Dynamic, Stream};


std::int32_t as_gl(Texture_filter texture_filter);
std::int32_t as_gl(Wrap_mode wrap_mode);
std::int32_t as_gl(Pixel_format pixel_format);
std::uint32_t as_gl(Usage_hint hint);


}  // namespace apeiron::opengl


#endif  // APEIRON_OPENGL_ENUMS_H

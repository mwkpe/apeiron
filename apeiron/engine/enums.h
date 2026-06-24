#ifndef APEIRON_ENGINE_ENUMS_H
#define APEIRON_ENGINE_ENUMS_H


#include <cstdint>


namespace apeiron::engine {


enum class Axis : std::uint8_t { X, Y, Z };
enum class Axis_order : std::uint8_t { XYZ, XZY, YXZ, YZX, ZXY, ZYX };


}  // namespace apeiron::engine


#endif  // APEIRON_ENGINE_ENUMS_H

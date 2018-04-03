#ifndef APEIRON_ENGINE_MODEL_FLAGS_H
#define APEIRON_ENGINE_MODEL_FLAGS_H


#include <cstdint>


namespace apeiron::engine::model_flags {


enum : std::uint32_t { vertices = 0x1, normals = 0x2, tex_coords = 0x4, colors = 0x8 };


}  // namespace apeiron::engine::model_flags


#endif  // APEIRON_ENGINE_MODEL_FLAGS_H

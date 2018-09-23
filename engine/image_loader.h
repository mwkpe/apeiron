#ifndef APEIRON_ENGINE_IMAGE_LOADER_H
#define APEIRON_ENGINE_IMAGE_LOADER_H


#include <cstdint>
#include <string_view>
#include <tuple>
#include <vector>


namespace apeiron::engine {


auto load_image(std::string_view filename, bool flip_y = true)
    -> std::tuple<std::vector<std::uint8_t>, int, int, int>;


}  // namespace apeiron::engine


#endif  //  APEIRON_ENGINE_IMAGE_LOADER_H

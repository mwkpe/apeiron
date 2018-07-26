#ifndef APEIRON_ENGINE_MODEL_LOADER_H
#define APEIRON_ENGINE_MODEL_LOADER_H


#include <cstdint>
#include <string_view>
#include <vector>
#include <tuple>


namespace apeiron::engine {


std::tuple<std::vector<float>, int> load_model(std::string_view filename, std::uint32_t flags);


}  // namespace apeiron::engine


#endif  // APEIRON_ENGINE_MODEL_LOADER_H

#ifndef APEIRON_ENGINE_MODEL_LOADER_H
#define APEIRON_ENGINE_MODEL_LOADER_H


#include <string_view>
#include <vector>
#include <tuple>


namespace apeiron::engine {


std::tuple<std::vector<float>, int> load_vertices(std::string_view filename);


}  // namespace apeiron::engine


#endif  //  APEIRON_ENGINE_MODEL_LOADER_H

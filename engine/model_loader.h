#ifndef APEIRON_ENGINE_MODEL_LOADER_H
#define APEIRON_ENGINE_MODEL_LOADER_H


#include <string_view>
#include <vector>


namespace apeiron::engine {


std::vector<float> load_vertices(std::string_view filename);


}  // namespace apeiron::engine


#endif  //  APEIRON_ENGINE_MODEL_LOADER_H

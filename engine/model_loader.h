#ifndef APEIRON_ENGINE_MODEL_LOADER_H
#define APEIRON_ENGINE_MODEL_LOADER_H


#include <string_view>
#include <vector>
#include "engine/vertex.h"


namespace apeiron::engine {


template<typename T = Vertex> std::vector<T> load_model(std::string_view filename);


}  // namespace apeiron::engine


#endif  // APEIRON_ENGINE_MODEL_LOADER_H

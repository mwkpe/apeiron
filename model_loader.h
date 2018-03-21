#ifndef APEIRON_MODEL_LOADER_H
#define APEIRON_MODEL_LOADER_H


#include <string_view>
#include <vector>


namespace apeiron {


std::vector<float> load_vertices(std::string_view filename);


}  // namespace apeiron


#endif  //  APEIRON_MODEL_LOADER_H

#ifndef APEIRON_PRIMITIVE_H
#define APEIRON_PRIMITIVE_H


#include <vector>
#include <glm/glm.hpp>
#include "engine/vertex.h"


namespace apeiron::engine::primitive {


template<typename T> std::vector<T> cube_vertices(glm::vec3 size,
    glm::vec3 position = glm::vec3{0.0f});
template<typename T> std::vector<T> cube_vertices(glm::vec3 size, glm::vec4 color,
    glm::vec3 position = glm::vec3{0.0f});


}  // namespace apeiron::engine::primitive


#endif  // APEIRON_PRIMITIVE_H

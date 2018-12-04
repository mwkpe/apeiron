#ifndef APEIRON_PRIMITIVE_H
#define APEIRON_PRIMITIVE_H


#include <vector>
#include <glm/glm.hpp>
#include "engine/vertex.h"


namespace apeiron::engine {


enum class Face { Front, Back, Left, Right, Up, Down };


}  // namespace engine


namespace apeiron::engine::primitive {


template<typename T = Vertex>
std::vector<T> quad_vertices(float width, float height,
    Face face = Face::Front, glm::vec3 position = glm::vec3{0.0f});
template<typename T = Vertex>
std::vector<T> quad_vertices(float width, float height, glm::vec4 color,
    Face face = Face::Front, glm::vec3 position = glm::vec3{0.0f});

template<typename T = Vertex>
std::vector<T> cuboid_vertices(glm::vec3 size, glm::vec3 position = glm::vec3{0.0f});
template<typename T = Vertex>
std::vector<T> cuboid_vertices(glm::vec3 size, glm::vec4 color,
    glm::vec3 position = glm::vec3{0.0f});


}  // namespace apeiron::engine::primitive


#endif  // APEIRON_PRIMITIVE_H

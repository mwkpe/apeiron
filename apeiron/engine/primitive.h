#ifndef APEIRON_PRIMITIVE_H
#define APEIRON_PRIMITIVE_H


#include <vector>
#include <glm/glm.hpp>
#include "apeiron/engine/vertex.h"


namespace apeiron::engine {


enum class Face { Front, Back, Left, Right, Up, Down };


}  // namespace engine


namespace apeiron::engine::primitive {


template<typename T = Vertex>
std::vector<T> quad_vertices(float width, float height,
    Face face = Face::Front, const glm::vec3& position = glm::vec3{0.0f});
template<typename T = Vertex>
std::vector<T> quad_vertices(float width, float height, const glm::vec4& color,
    Face face = Face::Front, const glm::vec3& position = glm::vec3{0.0f});
template<typename T = Vertex>
std::vector<T> quad_vertices(float width, float height, const glm::mat4& color,
    Face face = Face::Front, const glm::vec3& position = glm::vec3{0.0f});

template<typename T = Vertex>
std::vector<T> cuboid_vertices(const glm::vec3& size, const glm::vec3& position = glm::vec3{0.0f});
template<typename T = Vertex>
std::vector<T> cuboid_vertices(const glm::vec3& size, const glm::vec4& color,
    const glm::vec3& position = glm::vec3{0.0f});

template<typename T = Vertex> std::vector<T> disk_vertices(float radius, int points,
    Face face = Face::Front, const glm::vec3& position = glm::vec3{0.0f});
template<typename T = Vertex> std::vector<T> disk_vertices(float radius, int points,
    const glm::vec4& color, Face face = Face::Front, const glm::vec3& position = glm::vec3{0.0f});


}  // namespace apeiron::engine::primitive


#endif  // APEIRON_PRIMITIVE_H

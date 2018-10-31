#ifndef APEIRON_PRIMITIVE_H
#define APEIRON_PRIMITIVE_H


#include <vector>
#include <glm/glm.hpp>
#include "engine/vertex.h"


namespace apeiron::engine::primitive {


auto cube_vertices(glm::vec3 size, glm::vec4 color, glm::vec3 position = glm::vec3{0.0f})
    -> std::vector<Vertex>;
auto cube_vertices_simple(glm::vec3 size, glm::vec3 position = glm::vec3{0.0f})
    -> std::vector<Vertex_simple>;
auto cube_vertices_normal(glm::vec3 size, glm::vec3 position = glm::vec3{0.0f})
    -> std::vector<Vertex_normal>;
auto cube_vertices_color(glm::vec3 size, glm::vec4 color, glm::vec3 position = glm::vec3{0.0f})
    -> std::vector<Vertex_color>;
auto cube_vertices_texcoords(glm::vec3 size, glm::vec3 position = glm::vec3{0.0f})
    -> std::vector<Vertex_texcoords>;
auto cube_vertices_normal_color(glm::vec3 size, glm::vec4 color, glm::vec3 position = glm::vec3{0.0f})
    -> std::vector<Vertex_normal_color>;
auto cube_vertices_normal_texcoords(glm::vec3 size, glm::vec3 position = glm::vec3{0.0f})
    -> std::vector<Vertex_normal_texcoords>;


}  // namespace apeiron::engine::primitive


#endif  // APEIRON_PRIMITIVE_H

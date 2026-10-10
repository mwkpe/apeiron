#ifndef APEIRON_VERTEX_TRAITS_H
#define APEIRON_VERTEX_TRAITS_H


#include <concepts>


namespace apeiron::engine {


template<typename T> concept has_normal = requires(T v) {
  { v.normal } -> std::same_as<glm::vec3&>;
};

template<typename T> concept has_texcoords = requires(T v) {
  { v.texcoords } -> std::same_as<glm::vec2&>;
};

template<typename T> concept has_color = requires(T v) {
  { v.color } -> std::same_as<glm::vec4&>;
};

template<typename T> concept is_index_vertex = requires(T v) {
  { v.position } -> std::same_as<std::uint16_t&>;
  { v.color } -> std::same_as<std::uint8_t&>;
  { v.material } -> std::same_as<std::uint8_t&>;
};


}  // namespace apeiron::engine


#endif  // APEIRON_VERTEX_TRAITS_H

#ifndef APEIRON_VERTEX_H
#define APEIRON_VERTEX_H


#include <glm/glm.hpp>


namespace apeiron::engine::vertex::detail {


template<typename T = float> struct Position
{
  Position() = default;
  Position(T x, T y, T z) : x{x}, y{y}, z{z} {}
  Position(glm::tvec3<T> position) : x{position.x}, y{position.y}, z{position.z} {}
  T x;
  T y;
  T z;
};


template<typename T = float> struct Texcoords
{
  Texcoords() = default;
  Texcoords(T s, T t) : s{s}, t{t} {}
  Texcoords(glm::tvec2<T> texcoords) : s{texcoords.s}, t{texcoords.t} {}
  T s;
  T t;
};


template<typename T = float> struct Color
{
  Color() = default;
  Color(T r, T g, T b) : r{r}, g{g}, b{b}, a{1.0f} {}
  Color(T r, T g, T b, T a) : r{r}, g{g}, b{b}, a{a} {}
  Color(glm::tvec3<T> color) : r{color.r}, g{color.g}, b{color.b}, a{1.0f} {}
  Color(glm::tvec4<T> color) : r{color.r}, g{color.g}, b{color.b}, a{color.a} {}
  T r;
  T g;
  T b;
  T a;
};


template<typename T = float> struct Vertex
{
  Vertex() = default;
  Vertex(T x, T y, T z, T nx, T ny, T nz, T s, T t, T r, T g, T b)
      : position{x, y, z}, normal{nx, ny, nz}, texcoords{s, t}, color{r, g, b, 1.0f} {}
  Vertex(T x, T y, T z, T nx, T ny, T nz, T s, T t, T r, T g, T b, T a)
      : position{x, y, z}, normal{nx, ny, nz}, texcoords{s, t}, color{r, g, b, a} {}
  Vertex(glm::tvec3<T> position, glm::tvec3<T> normal, glm::tvec2<T> texcoords, glm::tvec3<T> color)
      : position{position}, normal{normal}, texcoords{texcoords}, color{color} {}
  Vertex(glm::tvec3<T> position, glm::tvec3<T> normal, glm::tvec2<T> texcoords, glm::tvec4<T> color)
      : position{position}, normal{normal}, texcoords{texcoords}, color{color} {}
  Position<T> position;
  Position<T> normal;
  Texcoords<T> texcoords;
  Color<T> color;
};


template<typename T = float> struct Vertex_simple
{
  Vertex_simple() = default;
  Vertex_simple(T x, T y, T z) : position{x, y, z} {}
  Vertex_simple(glm::tvec3<T> position) : position{position} {}
  Position<T> position;
};


template<typename T = float> struct Vertex_normal
{
  Vertex_normal() = default;
  Vertex_normal(T x, T y, T z, T nx, T ny, T nz)
      : position{x, y, z}, normal{nx, ny, nz} {}
  Vertex_normal(glm::tvec3<T> position, glm::tvec3<T> normal)
      : position{position}, normal{normal} {}
  Position<T> position;
  Position<T> normal;
};


template<typename T = float> struct Vertex_color
{
  Vertex_color() = default;
  Vertex_color(T x, T y, T z, T r, T g, T b)
      : position{x, y, z}, color{r, g, b, 1.0f} {}
  Vertex_color(T x, T y, T z, T r, T g, T b, T a)
      : position{x, y, z}, color{r, g, b, a} {}
  Vertex_color(glm::tvec3<T> position, glm::tvec4<T> color)
      : position{position}, color{color} {}
  Vertex_color(glm::tvec3<T> position, glm::tvec3<T> color)
      : position{position}, color{color} {}
  Position<T> position;
  Color<T> color;
};


template<typename T = float> struct Vertex_texcoords
{
  Vertex_texcoords() = default;
  Vertex_texcoords(T x, T y, T z, T s, T t)
      : position{x, y, z}, texcoords{s, t} {}
  Vertex_texcoords(glm::tvec3<T> position, glm::tvec2<T> texcoords)
      : position{position}, texcoords{texcoords} {}
  Position<T> position;
  Texcoords<T> texcoords;
};


template<typename T = float> struct Vertex_normal_color
{
  Vertex_normal_color() = default;
  Vertex_normal_color(T x, T y, T z, T nx, T ny, T nz, T r, T g, T b)
      : position{x, y, z}, normal{nx, ny, nz}, color{r, g, b, 1.0f} {}
  Vertex_normal_color(T x, T y, T z, T nx, T ny, T nz, T r, T g, T b, T a)
      : position{x, y, z}, normal{nx, ny, nz}, color{r, g, b, a} {}
  Vertex_normal_color(glm::tvec3<T> position, glm::tvec3<T> normal, glm::tvec3<T> color)
      : position{position}, normal{normal}, color{color} {}
  Vertex_normal_color(glm::tvec3<T> position, glm::tvec3<T> normal, glm::tvec4<T> color)
      : position{position}, normal{normal}, color{color} {}
  Position<T> position;
  Position<T> normal;
  Color<T> color;
};


template<typename T = float> struct Vertex_normal_texcoords
{
  Vertex_normal_texcoords() = default;
  Vertex_normal_texcoords(T x, T y, T z, T nx, T ny, T nz, T s, T t)
      : position{x, y, z}, normal{nx, ny, nz}, texcoords{s, t} {}
  Vertex_normal_texcoords(glm::tvec3<T> position, glm::tvec3<T> normal, glm::tvec2<T> texcoords)
      : position{position}, normal{normal}, texcoords{texcoords} {}
  Position<T> position;
  Position<T> normal;
  Texcoords<T> texcoords;
};


}  // namespace apeiron::engine::vertex::detail


namespace apeiron::engine::vertex {


using Position = detail::Position<float>;
using Color = detail::Color<float>;
using Texcoords = detail::Texcoords<float>;


}  // namespace apeiron::engine::vertex


namespace apeiron::engine {


using Vertex = vertex::detail::Vertex<float>;
using Vertex_simple = vertex::detail::Vertex_simple<float>;
using Vertex_normal = vertex::detail::Vertex_normal<float>;
using Vertex_color = vertex::detail::Vertex_color<float>;
using Vertex_texcoords = vertex::detail::Vertex_texcoords<float>;
using Vertex_normal_color = vertex::detail::Vertex_normal_color<float>;
using Vertex_normal_texcoords = vertex::detail::Vertex_normal_texcoords<float>;


}  // namespace apeiron::engine


#endif  // APEIRON_VERTEX_H

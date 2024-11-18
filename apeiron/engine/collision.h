#ifndef APEIRON_ENGINE_COLLISION_H
#define APEIRON_ENGINE_COLLISION_H


#include <optional>
#include <glm/glm.hpp>


namespace apeiron::engine::collision {


template<typename T = float> struct Point
{
  Point() = default;
  Point(T x, T y) : x{x}, y{y} {}
  T x;
  T y;
};


template<typename T = float> struct Rect
{
  Rect() = default;
  Rect(T x, T y, T w, T h) : x{x}, y{y}, w{w}, h{h} {}
  T x;
  T y;
  T w;
  T h;
};


struct Ray
{
  glm::vec3 position;
  glm::vec3 vector;
};


struct Sphere
{
  glm::vec3 position;
  float radius;
};


struct Plane
{
  glm::vec3 origin;
  glm::vec3 normal;
};


struct Quad
{
  glm::vec3 top_left;
  glm::vec3 top_right;
  glm::vec3 bottom_right;
  glm::vec3 bottom_left;
};


template<typename T> bool intersects(const Rect<T>& a, const Rect<T>& b)
{
  return ((a.x + a.w >= b.x && b.x + b.w >= a.x) && (a.y + a.h >= b.y && b.y + b.h >= a.y));
}


template<typename T> bool within(const Point<T>& p, const Rect<T>& r)
{
  return p.x > r.x && p.x < r.x + r.w && p.y > r.y && p.y < r.y + r.h;
}


template<typename T> bool within(const Rect<T>& a, const Rect<T>& b)
{
  return a.x > b.x && a.x + a.w < b.x + b.w && a.y > b.y && a.y + a.h < b.y + b.h;
}


Ray screen_raycast(float norm_x, float norm_y, const glm::mat4& inv_view_projection);
bool intersects(const Ray& ray, const Sphere& sphere);
bool intersects(const Ray& ray, const Quad& quad);
std::optional<glm::vec2> intersection_point(const Ray& ray, const Quad& quad);
std::optional<glm::vec3> intersection_point(const Ray& ray, const Plane& plane);


}  // namespace apeiron::engine::collision


#endif  // APEIRON_ENGINE_COLLISION_H

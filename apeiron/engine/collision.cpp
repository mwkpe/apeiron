#include "collision.h"


#include <cmath>


auto apeiron::engine::collision::screen_raycast(float norm_x, float norm_y,
    const glm::mat4& inv_view_projection) -> Ray
{
  auto near = glm::vec4{norm_x, norm_y, -1.0f, 1.0f};
  auto far = glm::vec4{norm_x, norm_y, 1.0f, 1.0f};
  auto near_world = inv_view_projection * near;
  auto far_world = inv_view_projection * far;
  near_world /= near_world.w;
  far_world /= far_world.w;
  return {glm::vec3{near_world}, glm::vec3{far_world - near_world}};
}


bool apeiron::engine::collision::intersects(const Ray& ray, const Sphere& sphere)
{
  auto distance = glm::length(glm::cross(sphere.position - ray.position,
      sphere.position - (ray.position + ray.vector))) / glm::length(ray.vector);
  return distance < sphere.radius;
}


bool apeiron::engine::collision::intersects(const Ray& ray, const Quad& quad)
{
  auto width = quad.top_right - quad.top_left;
  auto height = quad.bottom_left - quad.top_left;
  auto normal = glm::cross(width, height);

  float angle = glm::dot(glm::normalize(normal), glm::normalize(ray.vector));
  if (std::abs(angle) < 0.001f)  // 0 is 90 degrees to normal (parallel to quad's plane)
    return false;

  float growth = glm::dot(normal, ray.vector);
  float scale = glm::dot(-normal, ray.position - quad.top_left) / growth;
  auto point = ray.position + ray.vector * scale;
  auto d = point - quad.top_left;
  float u = glm::dot(d, width);
  float v = glm::dot(d, height);

  return u >= 0.0f && u <= glm::dot(width, width) &&
      v >= 0.0f && v <= glm::dot(height, height);
}


std::optional<glm::vec2> apeiron::engine::collision::intersection_point(const Ray& ray,
    const Quad& quad)
{
  auto width = quad.top_right - quad.top_left;
  auto height = quad.bottom_left - quad.top_left;
  auto normal = glm::cross(width, height);

  float angle = glm::dot(glm::normalize(normal), glm::normalize(ray.vector));
  if (std::abs(angle) < 0.001f)  // 0 is 90 degrees to normal (parallel to quad's plane)
    return std::nullopt;

  float growth = glm::dot(normal, ray.vector);
  float scale = glm::dot(-normal, ray.position - quad.top_left) / growth;
  auto point = ray.position + ray.vector * scale;
  auto d = point - quad.top_left;
  float u = glm::dot(d, glm::normalize(width));
  float v = glm::dot(d, glm::normalize(height));

  if (u >= 0.0f && u <= glm::length(width) && v >= 0.0f && v <= glm::length(height)) {
    return glm::vec2{u, v};
  }

  return std::nullopt;
}


std::optional<glm::vec3> apeiron::engine::collision::intersection_point(const Ray& ray,
    const Plane& plane)
{
  float angle = glm::dot(glm::normalize(plane.normal), glm::normalize(ray.vector));
  if (std::abs(angle) < 0.001f)  // 0 is 90 degrees to normal (parallel to plane)
    return std::nullopt;
  float growth = glm::dot(plane.normal, ray.vector);
  float scale = glm::dot(-plane.normal, ray.position - plane.origin) / growth;
  return ray.position + ray.vector * scale;
}

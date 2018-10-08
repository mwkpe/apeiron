#ifndef APEIRON_ENGINE_COLLISION_H
#define APEIRON_ENGINE_COLLISION_H


#include <cmath>
#include <glm/glm.hpp>


namespace apeiron::engine::collision {


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


struct Quad
{
  glm::vec3 top_left;
  glm::vec3 top_right;
  glm::vec3 bottom_right;
  glm::vec3 bottom_left;
};


inline Ray screen_raycast(float norm_x, float norm_y, const glm::mat4& inv_view_projection)
{
  auto near = glm::vec4{norm_x, norm_y, -1.0f, 1.0f};
  auto far = glm::vec4{norm_x, norm_y, 1.0f, 1.0f};
  auto near_world = inv_view_projection * near;
  auto far_world = inv_view_projection * far;
  near_world /= near_world.w;
  far_world /= far_world.w;
  return {glm::vec3{near_world}, glm::vec3{far_world - near_world}};
}


inline bool intersects(const Ray& ray, const Sphere& sphere)
{
  auto distance = glm::length(glm::cross(sphere.position - ray.position,
      sphere.position - (ray.position + ray.vector))) / glm::length(ray.vector);
  return distance < sphere.radius;
}


inline bool intersects(const Ray& ray, const Quad& quad)
{
  return false;
}


}  // namespace apeiron::engine::collision


#endif  // APEIRON_ENGINE_COLLISION_H

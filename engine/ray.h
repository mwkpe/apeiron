#ifndef APEIRON_ENGINE_RAY_H
#define APEIRON_ENGINE_RAY_H


#include <glm/glm.hpp>


namespace apeiron::engine {


struct Ray
{
  glm::vec3 position;
  glm::vec3 vector;
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


inline bool intersects(const Ray& ray, const Entity& entity)
{
  auto distance = glm::length(glm::cross(entity.position() - ray.position,
      entity.position() - (ray.position + ray.vector))) / glm::length(ray.vector);
  return distance < entity.intersection_radius();
}


}  // namespace apeiron::engine


#endif  // APEIRON_ENGINE_RAY_H

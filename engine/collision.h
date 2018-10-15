#ifndef APEIRON_ENGINE_COLLISION_H
#define APEIRON_ENGINE_COLLISION_H


#include <optional>
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


Ray screen_raycast(float norm_x, float norm_y, const glm::mat4& inv_view_projection);


bool intersects(const Ray& ray, const Sphere& sphere);
bool intersects(const Ray& ray, const Quad& quad);


std::optional<glm::vec3> intersection_point(const Ray& ray, const Plane& plane);


}  // namespace apeiron::engine::collision


#endif  // APEIRON_ENGINE_COLLISION_H

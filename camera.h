#ifndef APEIRON_CAMERA_H
#define APEIRON_CAMERA_H


#include <glm/glm.hpp>


namespace apeiron {


class Camera
{
public:
  enum class Direction { Forward, Backward, Left, Right };

  Camera();
  void reset();
  void move(Direction direction, float distances);
  void orient(int delta_x, int delta_y, float sensitivity);
  glm::mat4 view() const;

private:
  glm::vec3 position_;
  glm::vec3 front_;
  glm::vec3 right_;
  glm::vec3 up_;
  glm::vec3 world_up_;
  float pitch_ = 0.0f;
  float yaw_ = -90.0f;
};


}  // namespace apeiron


#endif  // APEIRON_CAMERA_H

#ifndef APEIRON_ENGINE_CAMERA_H
#define APEIRON_ENGINE_CAMERA_H


#include <glm/glm.hpp>


namespace apeiron::engine {


class Camera final
{
public:
  enum class Direction { Forward, Backward, Left, Right };
  explicit Camera(float pitch = 0.0f, float yaw = 0.0f,
      glm::vec3 position = glm::vec3{0.0f, 0.0f, 0.0f},
      glm::vec3 front = glm::vec3{0.0f, 0.0f, -1.0f},
      glm::vec3 world_up = glm::vec3{0.0f, 1.0f, 0.0f});
  void setup(float pitch = 0.0f, float yaw = 0.0f,
      glm::vec3 position = glm::vec3{0.0f, 0.0f, 0.0f},
      glm::vec3 front = glm::vec3{0.0f, 0.0f, -1.0f},
      glm::vec3 world_up = glm::vec3{0.0f, 1.0f, 0.0f});
  void move(Direction direction, float distances);
  void orient(int delta_x, int delta_y, float sensitivity);
  glm::mat4 view() const;

private:
  glm::vec3 position_ = glm::vec3{0.0f, 0.0f, 0.0f};
  glm::vec3 front_ = glm::vec3{0.0f, 0.0f, -1.0f};
  glm::vec3 world_up_= glm::vec3{0.0f, 1.0f, 0.0f};
  glm::vec3 right_;
  glm::vec3 up_;
  float pitch_ = 0.0f;
  float yaw_ = 0.0f;
};


}  // namespace apeiron::engine


#endif  // APEIRON_ENGINE_CAMERA_H

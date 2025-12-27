#ifndef APEIRON_ENGINE_TRANSFORM_H
#define APEIRON_ENGINE_TRANSFORM_H


#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>


namespace apeiron::engine {


enum class Rotation_axis : std::uint8_t { X, Y, Z };
enum class Rotation_order : std::uint8_t { XYZ, XZY, YXZ, YZX, ZXY, ZYX };


struct Rotation_component
{
  float angle_rad = 0.0f;
  glm::vec3 pivot = glm::vec3{0.0f};
};


class Transform
{
public:
  Transform& reset();

  Transform& reset_origin();
  Transform& reset_position();
  Transform& reset_scale();
  Transform& reset_rotation();

  Transform& set_origin(float x, float y, float z);
  Transform& set_origin(const glm::vec3& origin);
  Transform& set_position(float x, float y, float z);
  Transform& set_position(const glm::vec3& position);
  Transform& set_scale(float x, float y, float z);
  Transform& set_scale(const glm::vec3& scale);

  Transform& set_rotation_deg(float x, float y, float z);
  Transform& set_rotation_deg(const glm::vec3& rotation);
  Transform& set_rotation_rad(float x, float y, float z);
  Transform& set_rotation_rad(const glm::vec3& rotation);

  Transform& set_rotation_pivot(Rotation_axis axis, float x, float y, float z);
  Transform& set_rotation_pivot(Rotation_axis axis, const glm::vec3& origin);

  Transform& set_rotation_order(Rotation_order rotation_order);

  [[nodiscard]] glm::vec3 origin() const { return origin_; }
  [[nodiscard]] glm::vec3 position() const { return position_; }
  [[nodiscard]] glm::vec3 scale() const { return scale_; }

  [[nodiscard]] Rotation_order rotation_order() const { return rotation_order_; }
  [[nodiscard]] glm::vec3 rotation_rad() const;
  [[nodiscard]] glm::vec3 rotation_deg() const;
  [[nodiscard]] float rotation_rad(Rotation_axis axis) const;
  [[nodiscard]] float rotation_deg(Rotation_axis axis) const;

  [[nodiscard]] const glm::mat4& model_matrix() const;

private:
  void recompute() const;

  glm::vec3 origin_ = glm::vec3{0.0f, 0.0f, 0.0f};
  glm::vec3 position_ = glm::vec3{0.0f, 0.0f, 0.0f};
  glm::vec3 scale_ = glm::vec3{1.0f, 1.0f, 1.0f};

  Rotation_order rotation_order_ = Rotation_order::XYZ;
  Rotation_component rotation_x_ = {};
  Rotation_component rotation_y_ = {};
  Rotation_component rotation_z_ = {};

  mutable glm::mat4 model_matrix_ = glm::mat4{1.0f};
  mutable bool has_changed_ = true;
};


}  // namespace apeiron::engine


#endif  // APEIRON_ENGINE_TRANSFORM_H

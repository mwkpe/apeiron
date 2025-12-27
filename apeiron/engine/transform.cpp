#include "transform.h"


#include <glm/gtx/quaternion.hpp>


namespace {


inline void apply_rotation(glm::mat4& model, const glm::vec3& pivot, const glm::quat& q)
{
  model = glm::translate(model, pivot);
  model *= glm::toMat4(q);
  model = glm::translate(model, -pivot);
}


}  // namespace


auto apeiron::engine::Transform::reset() -> Transform&
{
  reset_origin();
  reset_position();
  reset_scale();
  reset_rotation();

  return *this;
}


auto apeiron::engine::Transform::reset_origin() -> Transform&
{
  origin_ = glm::vec3{0.0f, 0.0f, 0.0f};
  has_changed_ = true;
  return *this;
}


auto apeiron::engine::Transform::reset_position() -> Transform&
{
  position_ = glm::vec3{0.0f, 0.0f, 0.0f};
  has_changed_ = true;
  return *this;
}


auto apeiron::engine::Transform::reset_scale() -> Transform&
{
  scale_ = glm::vec3{1.0f, 1.0f, 1.0f};
  has_changed_ = true;
  return *this;
}


auto apeiron::engine::Transform::reset_rotation() -> Transform&
{
  rotation_x_ = {};
  rotation_y_ = {};
  rotation_z_ = {};

  has_changed_ = true;
  return *this;
}


auto apeiron::engine::Transform::set_origin(float x, float y, float z) -> Transform&
{
  origin_ = glm::vec3{x, y, z};
  has_changed_ = true;
  return *this;
}


auto apeiron::engine::Transform::set_origin(const glm::vec3& origin) -> Transform&
{
  origin_ = origin;
  has_changed_ = true;
  return *this;
}


auto apeiron::engine::Transform::set_position(float x, float y, float z) -> Transform&
{
  position_ = glm::vec3{x, y, z};
  has_changed_ = true;
  return *this;
}


auto apeiron::engine::Transform::set_position(const glm::vec3& position) -> Transform&
{
  position_ = position;
  has_changed_ = true;
  return *this;
}


auto apeiron::engine::Transform::set_scale(float x, float y, float z) -> Transform&
{
  scale_ = glm::vec3{x, y, z};
  has_changed_ = true;
  return *this;
}


auto apeiron::engine::Transform::set_scale(const glm::vec3& scale) -> Transform&
{
  scale_ = scale;
  has_changed_ = true;
  return *this;
}


auto apeiron::engine::Transform::set_rotation_deg(float x, float y, float z) -> Transform&
{
  rotation_x_.angle_rad = glm::radians(x);
  rotation_y_.angle_rad = glm::radians(y);
  rotation_z_.angle_rad = glm::radians(z);

  has_changed_ = true;
  return *this;
}


auto apeiron::engine::Transform::set_rotation_deg(const glm::vec3& rotation) -> Transform&
{
  rotation_x_.angle_rad = glm::radians(rotation.x);
  rotation_y_.angle_rad = glm::radians(rotation.y);
  rotation_z_.angle_rad = glm::radians(rotation.z);

  has_changed_ = true;
  return *this;
}


auto apeiron::engine::Transform::set_rotation_rad(float x, float y, float z) -> Transform&
{
  rotation_x_.angle_rad = x;
  rotation_y_.angle_rad = y;
  rotation_z_.angle_rad = z;

  has_changed_ = true;
  return *this;
}


auto apeiron::engine::Transform::set_rotation_rad(const glm::vec3& rotation) -> Transform&
{
  rotation_x_.angle_rad = rotation.x;
  rotation_y_.angle_rad = rotation.y;
  rotation_z_.angle_rad = rotation.z;

  has_changed_ = true;
  return *this;
}


auto apeiron::engine::Transform::set_rotation_pivot(Rotation_axis axis, float x, float y, float z)
    -> Transform&
{
  switch (axis) {
    case Rotation_axis::X: rotation_x_.pivot = glm::vec3{x, y, z}; break;
    case Rotation_axis::Y: rotation_y_.pivot = glm::vec3{x, y, z}; break;
    case Rotation_axis::Z: rotation_z_.pivot = glm::vec3{x, y, z}; break;
  }

  has_changed_ = true;
  return *this;
}


auto apeiron::engine::Transform::set_rotation_pivot(Rotation_axis axis, const glm::vec3& pivot)
    -> Transform&
{
  switch (axis) {
    case Rotation_axis::X: rotation_x_.pivot = pivot; break;
    case Rotation_axis::Y: rotation_y_.pivot = pivot; break;
    case Rotation_axis::Z: rotation_z_.pivot = pivot; break;
  }

  has_changed_ = true;

  return *this;
}


auto apeiron::engine::Transform::set_rotation_order(Rotation_order rotation_order) -> Transform&
{
  rotation_order_ = rotation_order;
  has_changed_ = true;
  return *this;
}


glm::vec3 apeiron::engine::Transform::rotation_rad() const
{
  return glm::vec3{rotation_x_.angle_rad, rotation_y_.angle_rad, rotation_z_.angle_rad};
}


glm::vec3 apeiron::engine::Transform::rotation_deg() const
{
  return glm::degrees(rotation_rad());
}


float apeiron::engine::Transform::rotation_rad(Rotation_axis axis) const
{
  switch (axis) {
    case Rotation_axis::X: return rotation_x_.angle_rad;
    case Rotation_axis::Y: return rotation_y_.angle_rad;
    case Rotation_axis::Z: return rotation_z_.angle_rad;
  }

  return 0.0f;
}


float apeiron::engine::Transform::rotation_deg(Rotation_axis axis) const
{
  return glm::degrees(rotation_rad(axis));
}


const glm::mat4& apeiron::engine::Transform::model_matrix() const
{
  if (has_changed_) {
    recompute();
  }

  return model_matrix_;
}


void apeiron::engine::Transform::recompute() const
{
  model_matrix_ = glm::mat4{1.0f};
  model_matrix_ = glm::translate(model_matrix_, origin_ + position_);

  const glm::quat qx = glm::angleAxis(rotation_x_.angle_rad, glm::vec3{1,0,0});
  const glm::quat qy = glm::angleAxis(rotation_y_.angle_rad, glm::vec3{0,1,0});
  const glm::quat qz = glm::angleAxis(rotation_z_.angle_rad, glm::vec3{0,0,1});

  switch (rotation_order_) {
    case Rotation_order::XYZ: {
      apply_rotation(model_matrix_, rotation_x_.pivot * scale_, qx);
      apply_rotation(model_matrix_, rotation_y_.pivot * scale_, qy);
      apply_rotation(model_matrix_, rotation_z_.pivot * scale_, qz);
    }
    break;
    case Rotation_order::XZY: {
      apply_rotation(model_matrix_, rotation_x_.pivot * scale_, qx);
      apply_rotation(model_matrix_, rotation_z_.pivot * scale_, qz);
      apply_rotation(model_matrix_, rotation_y_.pivot * scale_, qy);
    }
    break;
    case Rotation_order::YXZ: {
      apply_rotation(model_matrix_, rotation_y_.pivot * scale_, qy);
      apply_rotation(model_matrix_, rotation_x_.pivot * scale_, qx);
      apply_rotation(model_matrix_, rotation_z_.pivot * scale_, qz);
    }
    break;
    case Rotation_order::YZX: {
      apply_rotation(model_matrix_, rotation_y_.pivot * scale_, qy);
      apply_rotation(model_matrix_, rotation_z_.pivot * scale_, qz);
      apply_rotation(model_matrix_, rotation_x_.pivot * scale_, qx);
    }
    break;
    case Rotation_order::ZXY: {
      apply_rotation(model_matrix_, rotation_z_.pivot * scale_, qz);
      apply_rotation(model_matrix_, rotation_x_.pivot * scale_, qx);
      apply_rotation(model_matrix_, rotation_y_.pivot * scale_, qy);
    }
    break;
    case Rotation_order::ZYX: {
      apply_rotation(model_matrix_, rotation_z_.pivot * scale_, qz);
      apply_rotation(model_matrix_, rotation_y_.pivot * scale_, qy);
      apply_rotation(model_matrix_, rotation_x_.pivot * scale_, qx);
    }
    break;
  }

  model_matrix_ = glm::scale(model_matrix_, scale_);
  has_changed_ = false;
}

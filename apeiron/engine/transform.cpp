#include "transform.h"


#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/quaternion.hpp>


namespace {


inline void apply_rotation(glm::mat4& model, const apeiron::engine::Rotation_component& component)
{
  model = glm::translate(model, component.origin);
  model *= glm::toMat4(component.rotation);
  model = glm::translate(model, -component.origin);
}


}  // namespace


void apeiron::engine::Transform::reset_transform()
{
  reset_origin();
  reset_position();
  reset_scale();
  reset_rotation();
}


void apeiron::engine::Transform::reset_origin()
{
  origin = glm::vec3{0.0f, 0.0f, 0.0f};
}


void apeiron::engine::Transform::reset_position()
{
  position = glm::vec3{0.0f, 0.0f, 0.0f};
}


void apeiron::engine::Transform::reset_scale()
{
  scale = glm::vec3{1.0f, 1.0f, 1.0f};
}


void apeiron::engine::Transform::reset_rotation()
{
  rotation_x = {};
  rotation_y = {};
  rotation_z = {};
}


void apeiron::engine::Transform::set_rotation(const glm::quat& rotation)
{
  auto euler = glm::eulerAngles(rotation);
  rotation_x.rotation = glm::quat{glm::vec3{euler.x, 0.0f, 0.0f}};
  rotation_y.rotation = glm::quat{glm::vec3{0.0f, euler.y, 0.0f}};
  rotation_z.rotation = glm::quat{glm::vec3{0.0f, 0.0f, euler.z}};
}


void apeiron::engine::Transform::set_rotation_deg(float x, float y, float z)
{
  rotation_x.rotation = glm::quat{glm::vec3{glm::radians(x), 0.0f, 0.0f}};
  rotation_y.rotation = glm::quat{glm::vec3{0.0f, glm::radians(y), 0.0f}};
  rotation_z.rotation = glm::quat{glm::vec3{0.0f, 0.0f, glm::radians(z)}};
}


void apeiron::engine::Transform::set_rotation_deg(const glm::vec3& rotation)
{
  rotation_x.rotation = glm::quat{glm::vec3{glm::radians(rotation.x), 0.0f, 0.0f}};
  rotation_y.rotation = glm::quat{glm::vec3{0.0f, glm::radians(rotation.y), 0.0f}};
  rotation_z.rotation = glm::quat{glm::vec3{0.0f, 0.0f, glm::radians(rotation.z)}};
}


void apeiron::engine::Transform::set_rotation_rad(float x, float y, float z)
{
  rotation_x.rotation = glm::quat{glm::vec3{x, 0.0f, 0.0f}};
  rotation_y.rotation = glm::quat{glm::vec3{0.0f, y, 0.0f}};
  rotation_z.rotation = glm::quat{glm::vec3{0.0f, 0.0f, z}};
}


void apeiron::engine::Transform::set_rotation_rad(const glm::vec3& rotation)
{
  rotation_x.rotation = glm::quat{glm::vec3{rotation.x, 0.0f, 0.0f}};
  rotation_y.rotation = glm::quat{glm::vec3{0.0f, rotation.y, 0.0f}};
  rotation_z.rotation = glm::quat{glm::vec3{0.0f, 0.0f, rotation.z}};
}


void apeiron::engine::Transform::set_rotation_origin(Rotation_axis axis, float x, float y, float z)
{
  switch (axis) {
    case Rotation_axis::X: rotation_x.origin = glm::vec3{x, y, z}; break;
    case Rotation_axis::Y: rotation_y.origin = glm::vec3{x, y, z}; break;
    case Rotation_axis::Z: rotation_z.origin = glm::vec3{x, y, z}; break;
  }
}


void apeiron::engine::Transform::set_rotation_origin(Rotation_axis axis, const glm::vec3& origin)
{
  switch (axis) {
    case Rotation_axis::X: rotation_x.origin = origin; break;
    case Rotation_axis::Y: rotation_y.origin = origin; break;
    case Rotation_axis::Z: rotation_z.origin = origin; break;
  }
}


glm::mat4 apeiron::engine::Transform::model_matrix() const
{
  glm::mat4 model{1.0f};
  model = glm::translate(model, origin + position);

  switch (rotation_order) {
    case Rotation_order::XYZ: {
      apply_rotation(model, rotation_x);
      apply_rotation(model, rotation_y);
      apply_rotation(model, rotation_z);
    }
    break;
    case Rotation_order::XZY: {
      apply_rotation(model, rotation_x);
      apply_rotation(model, rotation_z);
      apply_rotation(model, rotation_y);
    }
    break;
    case Rotation_order::YXZ: {
      apply_rotation(model, rotation_y);
      apply_rotation(model, rotation_x);
      apply_rotation(model, rotation_z);
    }
    break;
    case Rotation_order::YZX: {
      apply_rotation(model, rotation_y);
      apply_rotation(model, rotation_z);
      apply_rotation(model, rotation_x);
    }
    break;
    case Rotation_order::ZXY: {
      apply_rotation(model, rotation_z);
      apply_rotation(model, rotation_x);
      apply_rotation(model, rotation_y);
    }
    break;
    case Rotation_order::ZYX: {
      apply_rotation(model, rotation_z);
      apply_rotation(model, rotation_y);
      apply_rotation(model, rotation_x);
    }
    break;
  }

  model = glm::scale(model, scale);

  return model;
}


glm::vec3 apeiron::engine::Transform::rotation_rad() const
{
  return glm::vec3{glm::eulerAngles(rotation_x.rotation).x,
      glm::eulerAngles(rotation_y.rotation).y,
      glm::eulerAngles(rotation_z.rotation).z};
}


glm::vec3 apeiron::engine::Transform::rotation_deg() const
{
  return glm::degrees(glm::vec3{glm::eulerAngles(rotation_x.rotation).x,
      glm::eulerAngles(rotation_y.rotation).y,
      glm::eulerAngles(rotation_z.rotation).z});
}


float apeiron::engine::Transform::rotation_rad(Rotation_axis axis) const
{
  switch (axis) {
    case Rotation_axis::X: return glm::eulerAngles(rotation_x.rotation).x;
    case Rotation_axis::Y: return glm::eulerAngles(rotation_y.rotation).y;
    case Rotation_axis::Z: return glm::eulerAngles(rotation_z.rotation).z;
  }

  return 0.0f;
}


float apeiron::engine::Transform::rotation_deg(Rotation_axis axis) const
{
  switch (axis) {
    case Rotation_axis::X: return glm::degrees(glm::eulerAngles(rotation_x.rotation).x);
    case Rotation_axis::Y: return glm::degrees(glm::eulerAngles(rotation_y.rotation).y);
    case Rotation_axis::Z: return glm::degrees(glm::eulerAngles(rotation_z.rotation).z);
  }

  return 0.0f;
}

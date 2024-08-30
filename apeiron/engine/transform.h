#ifndef APEIRON_ENGINE_TRANSFORM_H
#define APEIRON_ENGINE_TRANSFORM_H


#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>


namespace apeiron::engine {


enum class Rotation_axis : std::uint8_t { X, Y, Z };
enum class Rotation_order : std::uint8_t { XYZ, XZY, YXZ, YZX, ZXY, ZYX };


struct Rotation_component
{
  glm::quat rotation = glm::quat{1.0f, 0.0f, 0.0f, 0.0f};
  glm::vec3 origin = glm::vec3{0.0f};
};


class Transform
{
public:
  void reset_transform();
  void reset_origin();
  void reset_position();
  void reset_scale();
  void reset_rotation();

  void set_origin(float x, float y, float z) { origin = glm::vec3{x, y, z}; }
  void set_position(float x, float y, float z) { position = glm::vec3{x, y, z}; }
  void set_scale(float x, float y, float z) { scale = glm::vec3{x, y, z}; }

  void set_rotation(const glm::quat& rotation);
  void set_rotation_deg(float x, float y, float z);
  void set_rotation_deg(const glm::vec3& rotation);
  void set_rotation_rad(float x, float y, float z);
  void set_rotation_rad(const glm::vec3& rotation);

  void set_rotation_origin(Rotation_axis axis, float x, float y, float z);
  void set_rotation_origin(Rotation_axis axis, const glm::vec3& origin);

  [[nodiscard]] glm::vec3 rotation_rad() const;
  [[nodiscard]] glm::vec3 rotation_deg() const;
  [[nodiscard]] float rotation_rad(Rotation_axis axis) const;
  [[nodiscard]] float rotation_deg(Rotation_axis axis) const;

  [[nodiscard]] glm::mat4 model_matrix() const;

  glm::vec3 origin = glm::vec3{0.0f, 0.0f, 0.0f};
  glm::vec3 position = glm::vec3{0.0f, 0.0f, 0.0f};
  glm::vec3 scale = glm::vec3{1.0f, 1.0f, 1.0f};

  Rotation_order rotation_order = Rotation_order::XYZ;
  Rotation_component rotation_x = {};
  Rotation_component rotation_z = {};
  Rotation_component rotation_y = {};
};


}  // namespace apeiron::engine


#endif  // APEIRON_ENGINE_TRANSFORM_H

#include "shader_storage_buffer.h"


apeiron::opengl::Shader_storage_buffer::Shader_storage_buffer(Shader_storage_buffer&& other) noexcept
{
  id_ = other.id_;
  other.id_ = 0;

  binding_point_ = other.binding_point_;
  other.binding_point_ = invalid_binding_point_;

  binding_point_hardware_limit_ = other.binding_point_hardware_limit_;
  other.binding_point_hardware_limit_ = 0;
}


auto apeiron::opengl::Shader_storage_buffer::operator=(Shader_storage_buffer&& other) noexcept
    -> Shader_storage_buffer&
{
  if (&other == this) {
    return *this;
  }

  delete_buffer();

  id_ = other.id_;
  other.id_ = 0;

  binding_point_ = other.binding_point_;
  other.binding_point_ = invalid_binding_point_;

  binding_point_hardware_limit_ = other.binding_point_hardware_limit_;
  other.binding_point_hardware_limit_ = 0;

  return *this;
}


apeiron::opengl::Shader_storage_buffer::~Shader_storage_buffer()
{
  delete_buffer();
}


void apeiron::opengl::Shader_storage_buffer::delete_buffer()
{
  if (id_ > 0) {
    glDeleteBuffers(1, &id_);
    id_ = 0;
  }

  unbind();

  binding_point_ = invalid_binding_point_;
  binding_point_hardware_limit_ = 0;
}


void apeiron::opengl::Shader_storage_buffer::bind() const
{
  if (id_ > 0 && binding_point_ < invalid_binding_point_) {
    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, binding_point_, id_);
  }
}


void apeiron::opengl::Shader_storage_buffer::unbind() const
{
  if (binding_point_ < invalid_binding_point_) {
    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, binding_point_, 0);
  }
}

#include "command_buffer.h"


#include <glad/glad.h>
#include "apeiron/engine/error.h"


apeiron::opengl::Command_buffer::Command_buffer(Command_buffer&& other) noexcept
{
  id_ = other.id_;
  other.id_ = 0;

  capacity_ = other.capacity_;
  other.capacity_ = 0;
}


auto apeiron::opengl::Command_buffer::operator=(Command_buffer&& other) noexcept -> Command_buffer&
{
  if (&other == this) {
    return *this;
  }

  delete_buffer();

  id_ = other.id_;
  other.id_ = 0;

  capacity_ = other.capacity_;
  other.capacity_ = 0;

  return *this;
}


apeiron::opengl::Command_buffer::~Command_buffer()
{
  delete_buffer();
}


void apeiron::opengl::Command_buffer::delete_buffer()
{
  if (id_ > 0) {
    glDeleteBuffers(1, &id_);
    id_ = 0;
  }

  capacity_ = 0;
}


void apeiron::opengl::Command_buffer::init()
{
  delete_buffer();
  glGenBuffers(1, &id_);

  if (id_ == 0) {
    throw engine::Error{"Error creating command buffer"};
  }
}


void apeiron::opengl::Command_buffer::init(std::span<const Draw_command> commands)
{
  init();
  update(commands);
}


void apeiron::opengl::Command_buffer::update(std::span<const Draw_command> commands)
{
  if (id_ == 0) {
    return;
  }

  bind();

  if (commands.size_bytes() > capacity_) {
    glBufferData(GL_DRAW_INDIRECT_BUFFER, commands.size_bytes(), commands.data(), GL_DYNAMIC_DRAW);
    capacity_ = commands.size_bytes();
  }
  else {
    glBufferSubData(GL_DRAW_INDIRECT_BUFFER, 0, commands.size_bytes(), commands.data());
  }
}


void apeiron::opengl::Command_buffer::bind() const
{
  glBindBuffer(GL_DRAW_INDIRECT_BUFFER, id_);
}


void apeiron::opengl::Command_buffer::unbind() const
{
  glBindBuffer(GL_DRAW_INDIRECT_BUFFER, 0);
}

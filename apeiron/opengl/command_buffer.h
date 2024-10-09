#ifndef APEIRON_OPENGL_COMMAND_BUFFER_H
#define APEIRON_OPENGL_COMMAND_BUFFER_H


#include <cstdint>
#include <vector>


namespace apeiron::opengl {


struct Draw_command
{
  std::uint32_t vertex_count = 0;
  std::uint32_t instance_count = 0;
  std::uint32_t start_index = 0;
  std::uint32_t id = 0;
};


class Command_buffer
{
public:
  Command_buffer() = default;
  ~Command_buffer();
  Command_buffer(const Command_buffer&) = delete;
  Command_buffer(Command_buffer&&) noexcept;
  Command_buffer& operator=(const Command_buffer&) = delete;
  Command_buffer& operator=(Command_buffer&&) noexcept;

  void init();
  void init(const std::vector<Draw_command>& commands);
  void update(const std::vector<Draw_command>& commands);

  void bind() const;
  void unbind() const;

private:
  void delete_buffer();
  std::uint32_t id_ = 0;
};


}  // namespace apeiron::opengl


#endif  // APEIRON_OPENGL_COMMAND_BUFFER_H

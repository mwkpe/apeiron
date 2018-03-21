#ifndef APEIRON_MODEL_H
#define APEIRON_MODEL_H


#include <cstdint>
#include <string_view>


namespace apeiron {


class Model final
{
public:
  Model() = default;
  ~Model();
  // OpenGL delete calls in destructor
  Model(const Model&) = delete;
  Model(Model&&) = delete;
  Model& operator=(const Model&) = delete;
  Model& operator=(Model&&) = delete;

  void load(std::string_view filename);
  void render() const;

private:
  std::uint32_t vao_ = 0;
  std::uint32_t vbo_ = 0;
  std::uint32_t vertex_count_ = 0;
};


}  // namespace apeiron


#endif  // APEIRON_MODEL_H

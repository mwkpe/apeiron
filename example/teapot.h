#ifndef APEIRON_EXAMPLE_TEAPOT_H
#define APEIRON_EXAMPLE_TEAPOT_H


#include "engine/entity.h"
#include "opengl/model.h"


namespace apeiron::example {


class Teapot final : public engine::Entity
{
public:
  void load_model(std::string_view filename, std::uint32_t flags) { model_.load(filename, flags); }
  void render() const override { model_.render();  }

private:
  opengl::Model model_;
};


}  // namespace apeiron::example


#endif  // APEIRON_EXAMPLE_TEAPOT_H

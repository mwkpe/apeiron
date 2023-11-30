#ifndef APEIRON_EXAMPLE_MENU_H
#define APEIRON_EXAMPLE_MENU_H


#include "apeiron/opengl/gui.h"
#include "example/settings.h"


namespace apeiron::example {


class Menu final : public opengl::Gui
{
public:
  Menu(SDL_Window* window, SDL_GLContext context) : opengl::Gui{window, context} {}
  void setup(example::Settings* settings);
  void build(example::Settings* settings, float time);
  [[nodiscard]] bool has_mouse() const { return has_mouse_; }

private:
  bool has_mouse_ = false;
};


}  // namespace apeiron::example


#endif  // APEIRON_EXAMPLE_MENU_H

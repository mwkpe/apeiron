#ifndef APEIRON_EXAMPLE_MENU_H
#define APEIRON_EXAMPLE_MENU_H


#include "opengl/gui.h"
#include "example/options.h"


namespace apeiron::example {


class Menu final : public opengl::Gui
{
public:
  Menu(SDL_Window* window, SDL_GLContext context) : opengl::Gui{window, context} {}
  void setup(example::Options* options);
  void build(example::Options* options, float time);
  bool has_mouse() const { return has_mouse_; }

private:
  bool has_mouse_ = false;
};


}  // namespace apeiron::example


#endif  // APEIRON_EXAMPLE_MENU_H

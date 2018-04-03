#ifndef APEIRON_EXAMPLE_MENU_H
#define APEIRON_EXAMPLE_MENU_H


#include "opengl/gui.h"
#include "example/options.h"


namespace apeiron::example {


class Menu final : public opengl::Gui
{
public:
  explicit Menu(SDL_Window* window) : opengl::Gui{window} {}
  void setup(example::Options* options);
  void build(example::Options* options, float time);
};


}  // namespace apeiron::example


#endif  // APEIRON_EXAMPLE_MENU_H

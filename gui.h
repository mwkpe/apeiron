#ifndef APEIRON_GUI_H
#define APEIRON_GUI_H


#include "SDL2/SDL.h"


namespace apeiron {


class Gui
{
public:
  Gui(SDL_Window* window);
  void init();
  void process(SDL_Event* event);
  void render(float time);

private:
  SDL_Window* window_;
};


}  // namespace apeiron


#endif  // APEIRON_GUI_H

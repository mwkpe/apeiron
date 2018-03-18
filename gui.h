#ifndef APEIRON_GUI_H
#define APEIRON_GUI_H


#include "SDL2/SDL.h"
#include "options.h"


namespace apeiron {


class Gui
{
public:
  Gui(SDL_Window* window, Options& options) : window_{window}, options_{options} {}
  void init();
  void process(SDL_Event* event);
  void render(float time);

private:
  SDL_Window* window_;
  Options& options_;
};


}  // namespace apeiron


#endif  // APEIRON_GUI_H

#ifndef APEIRON_OPENGL_GUI_H
#define APEIRON_OPENGL_GUI_H


#include "SDL2/SDL.h"


namespace apeiron::opengl {


class Gui
{
public:
  Gui(SDL_Window* window) : window_{window} {}
  void init();
  void process(SDL_Event* event);
  void create_frame();
  void render();

protected:
  SDL_Window* window_;
};


}  // namespace apeiron::opengl


#endif  // APEIRON_OPENGL_GUI_H

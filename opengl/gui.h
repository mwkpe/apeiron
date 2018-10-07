#ifndef APEIRON_OPENGL_GUI_H
#define APEIRON_OPENGL_GUI_H


#include "SDL2/SDL.h"


namespace apeiron::opengl {


class Gui
{
public:
  explicit Gui(SDL_Window* window, SDL_GLContext context)
      : window_{window}, context_{context} {}
  void init();
  void process(SDL_Event* event);
  void create_frame();
  void render();

protected:
  SDL_Window* window_;
  SDL_GLContext context_;
};


}  // namespace apeiron::opengl


#endif  // APEIRON_OPENGL_GUI_H

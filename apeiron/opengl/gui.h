#ifndef APEIRON_OPENGL_GUI_H
#define APEIRON_OPENGL_GUI_H


#include <string_view>
#include "SDL2/SDL.h"


namespace apeiron::opengl {


class Gui
{
public:
  Gui(SDL_Window* window, SDL_GLContext context) : window_{window}, context_{context} {}
  void init(std::string_view glsl_version);  // E.g.: "#version 330" or "#version 460"
  void process(SDL_Event* event);
  void create_frame();
  void render() const;

protected:
  SDL_Window* window_;
  SDL_GLContext context_;
};


}  // namespace apeiron::opengl


#endif  // APEIRON_OPENGL_GUI_H

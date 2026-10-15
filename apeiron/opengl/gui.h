#ifndef APEIRON_OPENGL_GUI_H
#define APEIRON_OPENGL_GUI_H


#include <string_view>
#include <SDL3/SDL.h>


namespace apeiron::opengl {


class Gui
{
public:
  Gui(SDL_Window* window, SDL_GLContext context) : window_{window}, context_{context} {}
  ~Gui();
  Gui(const Gui&) = delete;
  Gui(Gui&&) noexcept;
  Gui& operator=(const Gui&) = delete;
  Gui& operator=(Gui&&) noexcept;

  void init(int gl_major, int gl_minor);
  void process(SDL_Event* event);
  void create_frame();
  void render() const;

protected:
  SDL_Window* window_;
  SDL_GLContext context_;

private:
  void shutdown();

  bool initialized_ = false;
};


}  // namespace apeiron::opengl


#endif  // APEIRON_OPENGL_GUI_H

#ifndef APEIRON_OPENGL_WINDOW_H
#define APEIRON_OPENGL_WINDOW_H


#include <string>
#include <string_view>
#include <tuple>
#include <SDL3/SDL.h>


namespace apeiron::opengl {


struct Window_settings
{
  std::string title = "Unknown";
  int init_flags = SDL_INIT_VIDEO;
  int width = 1280;
  int height = 720;
  bool ignore_scaling = false;
  bool resizable = false;
  bool fullscreen = false;
  bool vsync = false;
  int msaa_samples = 1;
  int gl_major = 3;
  int gl_minor = 3;
  bool gl_core = true;
};


struct Window_attributes
{
  int logical_width;
  int logical_height;
  int pixel_width;
  int pixel_height;
  float density;
  float scale;
};


class Window final
{
public:
  Window() = default;
  ~Window();
  Window(const Window&) = delete;
  Window(Window&& other) noexcept;
  Window& operator=(const Window&) = delete;
  Window& operator=(Window&& other) noexcept;

  void init(const Window_settings& settings);
  Window_attributes attributes() const;

  SDL_Window* sdl_window() { return window_; }
  SDL_GLContext gl_context() { return context_; }

private:
  SDL_Window* window_ = nullptr;
  SDL_GLContext context_ = nullptr;
};


}  // namespace apeiron::opengl


#endif  // APEIRON_OPENGL_WINDOW_H

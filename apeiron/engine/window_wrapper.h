#ifndef APEIRON_ENGINE_SDL_WINDOW_WRAPPER_H
#define APEIRON_ENGINE_SDL_WINDOW_WRAPPER_H


#include <string>
#include <string_view>
#include <tuple>
#include <SDL3/SDL.h>


namespace apeiron::engine {


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
  int render_width;
  int render_height;
  float scale;
};


class Window_wrapper final
{
public:
  Window_wrapper() = default;
  ~Window_wrapper();
  Window_wrapper(const Window_wrapper&) = delete;
  Window_wrapper(Window_wrapper&& other) noexcept;
  Window_wrapper& operator=(const Window_wrapper&) = delete;
  Window_wrapper& operator=(Window_wrapper&& other) noexcept;

  void init(const Window_settings& settings);
  Window_attributes attributes() const;

  SDL_Window* sdl_window() { return window_; }
  SDL_GLContext gl_context() { return context_; }

private:
  SDL_Window* window_ = nullptr;
  SDL_GLContext context_ = nullptr;
};


}  // namespace apeiron::engine


#endif  // APEIRON_ENGINE_SDL_WINDOW_WRAPPER_H

#ifndef APEIRON_ENGINE_SDL_WINDOW_WRAPPER_H
#define APEIRON_ENGINE_SDL_WINDOW_WRAPPER_H


#include <string>
#include <string_view>
#include <tuple>
#include <SDL3/SDL.h>


namespace apeiron::engine {


struct Window_settings
{
  std::string title;
  int init_flags;
  int width;
  int height;
  bool fullscreen;
  bool vsync;
  int msaa_samples;
  int gl_major;
  int gl_minor;
  bool gl_core;
};


struct Window_attributes
{
  int point_width;
  int point_height;
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

  Window_attributes init(const Window_settings& settings);

  SDL_Window* sdl_window() { return window_; }
  SDL_GLContext gl_context() { return context_; }

private:
  SDL_Window* window_ = nullptr;
  SDL_GLContext context_ = nullptr;
};


}  // namespace apeiron::engine


#endif  // APEIRON_ENGINE_SDL_WINDOW_WRAPPER_H

#ifndef APEIRON_ENGINE_SDL_WINDOW_WRAPPER_H
#define APEIRON_ENGINE_SDL_WINDOW_WRAPPER_H


#include <string_view>
#include <SDL3/SDL.h>


namespace apeiron::engine {


class Sdl_window_wrapper final
{
public:
  Sdl_window_wrapper() = default;
  ~Sdl_window_wrapper();
  Sdl_window_wrapper(const Sdl_window_wrapper&) = delete;
  Sdl_window_wrapper(Sdl_window_wrapper&& other) noexcept;
  Sdl_window_wrapper& operator=(const Sdl_window_wrapper&) = delete;
  Sdl_window_wrapper& operator=(Sdl_window_wrapper&& other) noexcept;

  void init(std::string_view title, int width, int height, bool fullscreen,
      int gl_major, int gl_minor, bool gl_core, bool vsync, int msaa_samples);

  SDL_Window* sdl_window() { return window_; }
  SDL_GLContext gl_context() { return context_; }

private:
  SDL_Window* window_ = nullptr;
  SDL_GLContext context_ = nullptr;
};


}  // namespace apeiron::engine


#endif  // APEIRON_ENGINE_SDL_WINDOW_WRAPPER_H

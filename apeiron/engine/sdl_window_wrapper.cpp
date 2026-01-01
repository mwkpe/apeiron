#include "sdl_window_wrapper.h"


#include <glad/glad.h>
#include "apeiron/engine/error.h"


apeiron::engine::Sdl_window_wrapper::~Sdl_window_wrapper()
{
  if (context_) {
    SDL_GL_DestroyContext(context_);
    context_ = nullptr;
  }
  
  if (window_) {
    SDL_DestroyWindow(window_);
    window_ = nullptr;
  }
    
  SDL_Quit();
}


apeiron::engine::Sdl_window_wrapper::Sdl_window_wrapper(Sdl_window_wrapper&& other) noexcept
{
  window_ = other.window_;
  context_ = other.context_;

  other.window_ = nullptr;
  other.context_ = nullptr;
}


auto apeiron::engine::Sdl_window_wrapper::operator=(Sdl_window_wrapper&& other) noexcept
    -> Sdl_window_wrapper&
{
  if (&other == this) {
    return *this;
  }

  window_ = other.window_;
  context_ = other.context_;

  other.window_ = nullptr;
  other.context_ = nullptr;

  return *this;
}


void apeiron::engine::Sdl_window_wrapper::init(std::string_view title, int width, int height,
    bool fullscreen, int gl_major, int gl_minor, bool gl_core, bool vsync, int msaa_samples)
{
  SDL_Init(SDL_INIT_VIDEO);

  if (gl_core) {
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
  }
  
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, gl_major);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, gl_minor);
  SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
  SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
  SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, msaa_samples);
  SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
  SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
  SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
  SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
  // On some AMD GPUs it seems to default to 16, make sure it's set to 24 bit
  SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
  SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);

  int window_flags = SDL_WINDOW_OPENGL;

  if (fullscreen) {
    window_flags |= SDL_WINDOW_FULLSCREEN;
  }

  window_ = SDL_CreateWindow(title.data(), width, height, window_flags);

  if (!window_) {
    throw Error{"Failed to create SDL window"};
  }

  context_ = SDL_GL_CreateContext(window_);

  if (!context_) {
    throw Error{"Failed to create OpenGL context"};
  }

  if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress)) {
    throw Error{"Failed to initialize OpenGL context"};
  }

  if (vsync) {
    SDL_GL_SetSwapInterval(1);
  }
  else {
    SDL_GL_SetSwapInterval(0);
  }
}

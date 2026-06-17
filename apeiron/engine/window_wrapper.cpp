#include "window_wrapper.h"


#include <iostream>
#include <cmath>
#include <glad/glad.h>
#include "apeiron/engine/error.h"


apeiron::engine::Window_wrapper::~Window_wrapper()
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


apeiron::engine::Window_wrapper::Window_wrapper(Window_wrapper&& other) noexcept
{
  window_ = other.window_;
  context_ = other.context_;

  other.window_ = nullptr;
  other.context_ = nullptr;
}


auto apeiron::engine::Window_wrapper::operator=(Window_wrapper&& other) noexcept
    -> Window_wrapper&
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


void apeiron::engine::Window_wrapper::init(const Window_settings& settings)
{
  SDL_Init(settings.init_flags);

  if (settings.gl_core) {
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
  }
  
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, settings.gl_major);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, settings.gl_minor);
  SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
  SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
  SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, settings.msaa_samples);
  SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
  SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
  SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
  SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
  // On some AMD GPUs it seems to default to 16, make sure it's set to 24 bit
  SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
  SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);

  int window_flags = SDL_WINDOW_OPENGL | SDL_WINDOW_HIGH_PIXEL_DENSITY;

  if (settings.fullscreen) {
    window_flags |= SDL_WINDOW_FULLSCREEN;
  }
  else {
    window_flags |= SDL_WINDOW_RESIZABLE;
  }

  window_ = SDL_CreateWindow(settings.title.data(), settings.width, settings.height, window_flags);

  if (!window_) {
    throw Error{"Failed to create SDL window"};
  }

  int logical_width = settings.width;
  int logical_height = settings.height;
  int render_width = settings.width;
  int render_height = settings.height;
  float density = SDL_GetWindowPixelDensity(window_);

  if (settings.fullscreen) {
    SDL_SyncWindow(window_);
    SDL_GetWindowSizeInPixels(window_, &render_width, &render_height);
    SDL_GetWindowSize(window_, &logical_width, &logical_height);
  }
  else if (settings.ignore_scaling && density > 1.0f) {
    // Set logical size so that the resulting pixel size is roughly the requested size
    logical_width = std::lround(static_cast<float>(settings.width) / density);
    logical_height = std::lround(static_cast<float>(settings.height) / density);
    SDL_SetWindowSize(window_, logical_width, logical_height);
    SDL_SyncWindow(window_);
    SDL_GetWindowSizeInPixels(window_, &render_width, &render_height);
  }

  context_ = SDL_GL_CreateContext(window_);

  if (!context_) {
    throw Error{"Failed to create OpenGL context"};
  }

  if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress)) {
    throw Error{"Failed to initialize OpenGL context"};
  }

  if (!SDL_GL_SetSwapInterval(settings.vsync ? 1 : 0)) {
    std::cerr << "Setting swap interval failed: " << SDL_GetError() << std::endl;
  }
}


auto apeiron::engine::Window_wrapper::attributes() const -> Window_attributes
{
  float density = SDL_GetWindowPixelDensity(window_);
  int logical_width;
  int logical_height;
  int render_width;
  int render_height;

  SDL_SyncWindow(window_);
  SDL_GetWindowSize(window_, &logical_width, &logical_height);
  SDL_GetWindowSizeInPixels(window_, &render_width, &render_height);

  return {logical_width, logical_height, render_width, render_height, density};
}

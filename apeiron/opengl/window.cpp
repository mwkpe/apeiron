#include "window.h"


#include <iostream>
#include <cmath>
#include <glad/glad.h>
#include "apeiron/engine/error.h"


apeiron::opengl::Window::~Window()
{
  destroy();
}


apeiron::opengl::Window::Window(Window&& other) noexcept
{
  window_ = other.window_;
  context_ = other.context_;
  sdl_initialized_ = other.sdl_initialized_;

  other.window_ = nullptr;
  other.context_ = nullptr;
  other.sdl_initialized_ = false;
}


auto apeiron::opengl::Window::operator=(Window&& other) noexcept
    -> Window&
{
  if (&other == this) {
    return *this;
  }

  destroy();

  window_ = other.window_;
  context_ = other.context_;
  sdl_initialized_ = other.sdl_initialized_;

  other.window_ = nullptr;
  other.context_ = nullptr;
  other.sdl_initialized_ = false;

  return *this;
}


void apeiron::opengl::Window::destroy()
{
  if (context_) {
    SDL_GL_DestroyContext(context_);
    context_ = nullptr;
  }

  if (window_) {
    SDL_DestroyWindow(window_);
    window_ = nullptr;
  }

  if (sdl_initialized_) {
    SDL_Quit();
    sdl_initialized_ = false;
  }
}


void apeiron::opengl::Window::init(const Window_settings& settings)
{
  destroy();

  if (!SDL_Init(settings.init_flags)) {
    throw engine::Error::format("Failed to initialize SDL: {}", SDL_GetError());
  }

  sdl_initialized_ = true;

  if (settings.gl_core) {
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
  }

  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, settings.gl_major);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, settings.gl_minor);
  SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
  const bool multisample = settings.msaa_samples > 1;
  SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, multisample ? 1 : 0);
  SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, multisample ? settings.msaa_samples : 0);
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
  else if (settings.resizable) {
    window_flags |= SDL_WINDOW_RESIZABLE;
  }

  window_ = SDL_CreateWindow(settings.title.data(), settings.width, settings.height, window_flags);

  if (!window_) {
    throw engine::Error{"Failed to create SDL window"};
  }

  if (float density = SDL_GetWindowPixelDensity(window_);
      !settings.fullscreen && settings.ignore_scaling && SDL_GetWindowPixelDensity(window_) > 1.0f) {
    // Set logical size so that the resulting pixel size is roughly the requested size
    const auto logical_width = std::lround(static_cast<float>(settings.width) / density);
    const auto logical_height = std::lround(static_cast<float>(settings.height) / density);
    SDL_SetWindowSize(window_, logical_width, logical_height);
  }

  SDL_SyncWindow(window_);
  context_ = SDL_GL_CreateContext(window_);

  if (!context_) {
    throw engine::Error{"Failed to create OpenGL context"};
  }

  if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress)) {
    throw engine::Error{"Failed to initialize OpenGL context"};
  }

  if (!SDL_GL_SetSwapInterval(settings.vsync ? 1 : 0)) {
    std::cerr << "Setting swap interval failed: " << SDL_GetError() << std::endl;
  }
}


auto apeiron::opengl::Window::attributes() const -> Window_attributes
{
  int logical_width;
  int logical_height;
  int pixel_width;
  int pixel_height;

  SDL_SyncWindow(window_);
  SDL_GetWindowSize(window_, &logical_width, &logical_height);
  SDL_GetWindowSizeInPixels(window_, &pixel_width, &pixel_height);

  return {logical_width, logical_height, pixel_width, pixel_height,
      SDL_GetWindowPixelDensity(window_), SDL_GetWindowDisplayScale(window_)};
}

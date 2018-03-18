#include <iostream>
#include "SDL2/SDL.h"
#include "GL/glew.h"
#include "options.h"
#include "error.h"
#include "gui.h"
#include "world.h"


int main(int argc, char *argv[])
{
  SDL_Init(SDL_INIT_VIDEO);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
  SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
  SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
  SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 16);

  auto* window = SDL_CreateWindow("Apeiron", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
      1280, 720, SDL_WINDOW_OPENGL);
  auto context = SDL_GL_CreateContext(window);

  glewExperimental = GL_TRUE;
  if (GLenum status = glewInit(); status != GLEW_OK) {
    std::cerr << reinterpret_cast<const char*>(glewGetErrorString(status));
    return 1;
  }

  SDL_GL_SetSwapInterval(1);

  apeiron::Options options;
  apeiron::World world(options);
  apeiron::Gui gui(window, options);
  try {
    world.init();
    gui.init();
  }
  catch (const apeiron::Error& e) {
    std::cerr << e.what() << std::endl;
    return 1;
  }

  while (!options.quit) {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
      gui.process(&event);
      options.quit = event.type == SDL_QUIT;
      switch (event.type) {
        case SDL_KEYDOWN: {
          switch (event.key.keysym.sym) {
            case SDLK_F1:
              options.show_gui = !options.show_gui;
              break;
            case SDLK_F2:
              options.wireframe = !options.wireframe;
              break;
          }
        } break;
      }
    }

    glEnable(GL_DEPTH_TEST);
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    auto time = SDL_GetTicks() / 1000.0f;
    world.render(time);
    if (options.show_gui)
      gui.render(time);

    SDL_GL_SwapWindow(window);
  }

  SDL_GL_DeleteContext(context);
  SDL_DestroyWindow(window);
  SDL_Quit();

  return 0;
}

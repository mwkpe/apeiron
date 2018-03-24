#include <iostream>
#include "SDL2/SDL.h"
#include "GL/glew.h"
#include "engine/error.h"
#include "engine/input.h"
#include "example/options.h"
#include "example/menu.h"
#include "example/world.h"


namespace {


apeiron::engine::Input get_input_state()
{
  apeiron::engine::Input input;
  const std::uint8_t* kb_state = SDL_GetKeyboardState(nullptr);

  input.forward = kb_state[SDL_SCANCODE_UP] || kb_state[SDL_SCANCODE_W];
  input.backward = kb_state[SDL_SCANCODE_DOWN] || kb_state[SDL_SCANCODE_S];
  input.left = kb_state[SDL_SCANCODE_LEFT] || kb_state[SDL_SCANCODE_A];
  input.right = kb_state[SDL_SCANCODE_RIGHT] || kb_state[SDL_SCANCODE_D];

  SDL_GetMouseState(&input.mouse_x_abs, &input.mouse_y_abs);
  SDL_GetRelativeMouseState(&input.mouse_x_rel, &input.mouse_y_rel);
  input.mouse_y_rel = -input.mouse_y_rel;  // Make mouse up correspond to camera pitch up

  return input;
}


}  // namespace


int main(int argc, char* argv[])
{
  SDL_Init(SDL_INIT_VIDEO);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
  SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
  SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
  SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 1);

  auto* window = SDL_CreateWindow("Apeiron", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
      1280, 720, SDL_WINDOW_OPENGL);
  auto context = SDL_GL_CreateContext(window);

  glewExperimental = GL_TRUE;
  if (GLenum status = glewInit(); status != GLEW_OK) {
    std::cerr << reinterpret_cast<const char*>(glewGetErrorString(status));
    return 1;
  }

  SDL_GL_SetSwapInterval(0);

  apeiron::example::Options options;
  apeiron::example::World world(&options);
  apeiron::example::Menu menu(window);
  try {
    world.init();
    menu.init();
    menu.setup(&options);
  }
  catch (const apeiron::engine::Error& e) {
    std::cerr << e.what() << std::endl;
    return 1;
  }

  auto frame_timer = [&options, last_ticks = SDL_GetTicks()]() mutable {
    auto current_ticks = SDL_GetTicks();
    auto elapsed = current_ticks - last_ticks;
    if (auto target = 1000u / options.max_fps; options.limit_fps && elapsed < target) {
      SDL_Delay(target - elapsed);
      current_ticks = SDL_GetTicks();
      elapsed = current_ticks - last_ticks;
    }
    last_ticks = current_ticks;
    return elapsed;
  };

  while (!options.quit) {
    auto elapsed = frame_timer();  // May also delay and hence limits fps
    float delta_time = elapsed / 1000.0f;

    SDL_Event event;
    while (SDL_PollEvent(&event)) {
      menu.process(&event);
      options.quit = event.type == SDL_QUIT;
      switch (event.type) {
        case SDL_KEYDOWN: {
          switch (event.key.keysym.sym) {
            case SDLK_F1:
              options.show_gui = !options.show_gui;
              if (options.show_gui) {
                SDL_CaptureMouse(SDL_FALSE);
                SDL_SetRelativeMouseMode(SDL_FALSE);
              }
              else {
                SDL_GetRelativeMouseState(nullptr, nullptr);  // Prevent erroneous movement
                SDL_CaptureMouse(SDL_TRUE);
                SDL_SetRelativeMouseMode(SDL_TRUE);
              }
              break;
            case SDLK_F2:
              options.wireframe = !options.wireframe;
              break;
            case SDLK_F3:
              world.reset();
              break;
          }
        } break;
      }
    }

    if (!options.show_gui) {
      auto input = get_input_state();
      world.update(delta_time, &input);
    }
    else {  // imgui handles input
      world.update(delta_time);
    }

    glEnable(GL_DEPTH_TEST);
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    auto time = SDL_GetTicks() / 1000.0f;
    world.render(time);
    if (options.show_gui) {
      menu.build(&options, time);
      menu.render();
    }

    SDL_GL_SwapWindow(window);
  }

  SDL_GL_DeleteContext(context);
  SDL_DestroyWindow(window);
  SDL_Quit();

  return 0;
}

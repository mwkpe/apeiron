#include <cstdint>
#include <memory>
#include <iostream>
#ifdef _WIN32
  #define WIN32_LEAN_AND_MEAN
  #include <windows.h>
#endif
#include <SDL3/SDL.h>
#include <glad/glad.h>
#include "apeiron/engine/error.h"
#include "apeiron/engine/event.h"
#include "apeiron/engine/input.h"
#include "apeiron/engine/sdl_input.h"
#include "example/settings.h"
#include "example/menu.h"
#include "example/world.h"


namespace {


void disable_dpi_scaling()
{
  // Silence gcc >= 8 warning about the winapi function cast
  #pragma GCC diagnostic push
  #pragma GCC diagnostic ignored "-Wcast-function-type"

  #ifdef _WIN32
    enum { PROCESS_DPI_UNAWARE, PROCESS_SYSTEM_DPI_AWARE, PROCESS_PER_MONITOR_DPI_AWARE };
    auto free_module = [](HMODULE module){ FreeLibrary(module); };
    using mp = std::unique_ptr<std::remove_pointer<HMODULE>::type, decltype(free_module)>;
    if (auto shcore = mp{LoadLibrary("Shcore.dll"), free_module}) {
      using fp = HRESULT(WINAPI*)(int);
      if (auto f = reinterpret_cast<fp>(GetProcAddress(shcore.get(), "SetProcessDpiAwareness"))) {
        if (f(PROCESS_SYSTEM_DPI_AWARE) != S_OK) {
          std::cerr << "Could not disable DPI scaling" << std::endl;
        }
      }
    }
  #endif

  #pragma GCC diagnostic pop
}


}  // namespace


int main([[maybe_unused]] int argc, [[maybe_unused]] char* argv[])
{
  disable_dpi_scaling();

  apeiron::example::Settings settings;
  try {
    settings = apeiron::example::load_settings("settings.toml");
  }
  catch (const apeiron::engine::Warning& w) {
    std::cout << w.what() << std::endl;
  }

  SDL_Init(SDL_INIT_VIDEO);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 6);
  SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
  SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
  SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, settings.msaa_samples);

  auto* window = SDL_CreateWindow("apeiron", settings.window_width, settings.window_height,
      SDL_WINDOW_OPENGL);
  auto context = SDL_GL_CreateContext(window);

  auto quit_sdl = [&]{
    SDL_GL_DestroyContext(context);
    SDL_DestroyWindow(window);
    SDL_Quit();
  };

  if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress)) {
    std::cerr << "Failed to initialize OpenGL context" << std::endl;
    quit_sdl();
    std::cin.ignore();  // Keep console open
    return 1;
  }

  if (settings.vsync) {
    SDL_GL_SetSwapInterval(1);
  }
  else {
    SDL_GL_SetSwapInterval(0);
  }

  apeiron::example::World world(&settings);
  apeiron::example::Menu menu(window, context);

  try {
    world.init();
    menu.init("#version 460");
    menu.setup(&settings);
  }
  catch (const apeiron::engine::Error& e) {
    std::cerr << e.what() << std::endl;
    quit_sdl();
    std::cin.ignore();  // Keep console open
    return 1;
  }

  auto frame_timer = [&settings, last_ticks = SDL_GetTicksNS()] mutable {
    auto current_ticks = SDL_GetTicksNS();
    auto elapsed = current_ticks - last_ticks;

    if (auto target = 1'000'000'000ull / settings.max_fps; settings.limit_fps && elapsed < target) {
      SDL_DelayPrecise(target - elapsed);
      current_ticks = SDL_GetTicksNS();
      elapsed = current_ticks - last_ticks;
    }

    last_ticks = current_ticks;
    return elapsed;
  };

  std::vector<apeiron::engine::Event> events;

  while (!settings.quit) {
    auto elapsed = frame_timer();  // May also delay and hence limits fps
    float delta_time = static_cast<float>(elapsed) / 1000'000'000.0f;
    auto time = static_cast<float>(SDL_GetTicks()) / 1000.0f;

    SDL_Event event;

    while (SDL_PollEvent(&event)) {
      if (settings.show_menu) {
        menu.process(&event);
      }

      settings.quit = event.type == SDL_EVENT_QUIT;

      switch (event.type) {
        case SDL_EVENT_KEY_DOWN: {
          switch (event.key.key) {
            case SDLK_ESCAPE:
              settings.quit = true;
              break;
            case SDLK_F1:
              settings.show_menu = !settings.show_menu;

              if (settings.show_menu) {
                SDL_CaptureMouse(false);
                SDL_SetWindowRelativeMouseMode(window, false);
              }
              else {
                SDL_GetRelativeMouseState(nullptr, nullptr);  // Prevent erroneous movement
                SDL_CaptureMouse(true);
                SDL_SetWindowRelativeMouseMode(window, true);
              }
              break;
            case SDLK_F4:
              settings.wireframe = !settings.wireframe;
              break;
          }
        } break;
        case SDL_EVENT_MOUSE_MOTION: {
          if (!menu.has_mouse()) {
            events.emplace_back(apeiron::engine::Mouse_motion_event{event.motion.x, event.motion.y,
                event.motion.xrel, event.motion.yrel});
          }
        } break;
        case SDL_EVENT_MOUSE_BUTTON_UP: {
          if (!menu.has_mouse()) {
            events.emplace_back(apeiron::engine::Mouse_button_up_event{
                apeiron::engine::get_mouse_button(event.button.button),
                event.button.x, event.button.y});
          }
        } break;
        case SDL_EVENT_MOUSE_BUTTON_DOWN: {
          if (!menu.has_mouse()) {
              events.emplace_back(apeiron::engine::Mouse_button_down_event{
                  apeiron::engine::get_mouse_button(event.button.button),
                  event.button.x, event.button.y});
          }
        } break;
        case SDL_EVENT_MOUSE_WHEEL: {
          if (!menu.has_mouse()) {
            events.emplace_back(apeiron::engine::Mouse_wheel_event{event.wheel.x, event.wheel.y});
          }
        } break;
        default:;
      }
    }

    auto input = apeiron::engine::get_input_state();
    world.update(time, delta_time, events, &input);
    events.clear();

    glCullFace(GL_BACK);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);

    world.render();

    if (settings.show_menu) {
      menu.build(&settings, time);
      menu.render();
    }

    SDL_GL_SwapWindow(window);
  }

  quit_sdl();
  apeiron::example::save_settings(settings, "settings.toml");

  return 0;
}

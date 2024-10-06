#include <cstdint>
#include <memory>
#include <iostream>
#ifdef _WIN32
  #define WIN32_LEAN_AND_MEAN
  #include <windows.h>
#endif
#include "SDL2/SDL.h"
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
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
  SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
  SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
  SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, settings.msaa_samples);

  auto* window = SDL_CreateWindow("apeiron", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
      settings.window_width, settings.window_height, SDL_WINDOW_OPENGL);
  auto context = SDL_GL_CreateContext(window);
  auto quit_sdl = [&]{
    SDL_GL_DeleteContext(context);
    SDL_DestroyWindow(window);
    SDL_Quit();
  };

  if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress)) {
    std::cerr << "Failed to initialize OpenGL context" << std::endl;
    quit_sdl();
    std::cin.ignore();  // Keep console open
    return 1;
  }

//  if (glewIsSupported("GL_EXT_texture_filter_anisotropic")) {
//    GLint max_anisotropy = 1;
//    glGetIntegerv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &max_anisotropy);
//    if (max_anisotropy > 1)
//      settings.af_samples = max_anisotropy;
//  }

  if (settings.vsync)
    SDL_GL_SetSwapInterval(1);
  else
    SDL_GL_SetSwapInterval(0);

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

  auto frame_timer = [&settings, last_ticks = SDL_GetTicks()](bool benchmarking) mutable {
    auto current_ticks = SDL_GetTicks();
    auto elapsed = current_ticks - last_ticks;
    if (auto target = 1000u / settings.max_fps; !benchmarking && settings.limit_fps && elapsed < target) {
      SDL_Delay(target - elapsed);
      current_ticks = SDL_GetTicks();
      elapsed = current_ticks - last_ticks;
    }
    last_ticks = current_ticks;
    return elapsed;
  };

  bool benchmarking = false;
  float benchmark_start_time = 0;
  int benchmark_total_frames = 0;
  std::vector<apeiron::engine::Event> events;

  while (!settings.quit) {
    auto elapsed = frame_timer(benchmarking);  // May also delay and hence limits fps
    float delta_time = static_cast<float>(elapsed) / 1000.0f;
    auto time = static_cast<float>(SDL_GetTicks()) / 1000.0f;

    SDL_Event event;
    while (SDL_PollEvent(&event)) {
      if (settings.show_menu) {
        menu.process(&event);
      }
      settings.quit = event.type == SDL_QUIT;
      switch (event.type) {
        case SDL_KEYDOWN: {
          switch (event.key.keysym.sym) {
            case SDLK_ESCAPE:
              settings.quit = true;
              break;
            case SDLK_F1:
              settings.show_menu = !settings.show_menu;
              if (settings.show_menu) {
                SDL_CaptureMouse(SDL_FALSE);
                SDL_SetRelativeMouseMode(SDL_FALSE);
              }
              else {
                SDL_GetRelativeMouseState(nullptr, nullptr);  // Prevent erroneous movement
                SDL_CaptureMouse(SDL_TRUE);
                SDL_SetRelativeMouseMode(SDL_TRUE);
              }
              break;
            case SDLK_F4:
              settings.wireframe = !settings.wireframe;
              break;
            case SDLK_F6:
              if (!benchmarking) {
                benchmarking = true;
                benchmark_start_time = time;
                benchmark_total_frames = 0;
                std::cout << "Benchmark started... (takes 10s)" << std::endl;
              }
              break;
            default:;
          }
        } break;
        case SDL_MOUSEMOTION: {
          if (!menu.has_mouse()) {
            events.emplace_back(apeiron::engine::Mouse_motion_event{event.motion.x, event.motion.y,
                event.motion.xrel, event.motion.yrel});
          }
        } break;
        case SDL_MOUSEBUTTONUP: {
          if (!menu.has_mouse()) {
            events.emplace_back(apeiron::engine::Mouse_button_up_event{
                apeiron::engine::get_mouse_button(event.button.button),
                event.button.x, event.button.y});
          }
        } break;
        case SDL_MOUSEBUTTONDOWN: {
          if (!menu.has_mouse()) {
              events.emplace_back(apeiron::engine::Mouse_button_down_event{
                  apeiron::engine::get_mouse_button(event.button.button),
                  event.button.x, event.button.y});
          }
        } break;
        case SDL_MOUSEWHEEL: {
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

    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    world.render();
    if (settings.show_menu) {
      menu.build(&settings, time);
      menu.render();
    }

    SDL_GL_SwapWindow(window);

    if (benchmarking) {
      benchmark_total_frames++;
      if (time > benchmark_start_time + 10.0f) {
        benchmarking = false;
        std::cout << "Benchmark result: " << benchmark_total_frames / 10 << " fps" << std::endl;
      }
    }
  }

  quit_sdl();
  apeiron::example::save_settings(settings, "settings.toml");

  return 0;
}

#include <iostream>

#include <SDL3/SDL.h>

#include "apeiron/engine/error.h"
#include "apeiron/engine/event.h"
#include "apeiron/engine/input.h"
#include "apeiron/engine/sdl_input.h"
#include "apeiron/engine/window_wrapper.h"

#include "example/settings.h"
#include "example/menu.h"
#include "example/world.h"


int main([[maybe_unused]] int argc, [[maybe_unused]] char* argv[])
{
  apeiron::example::Settings settings;
  apeiron::engine::Window_wrapper window;

  try {
    settings = apeiron::example::load_settings("settings.toml");
  }
  catch (const apeiron::engine::Warning& w) {
    std::cout << w.what() << std::endl;
  }

  try {
    apeiron::engine::Window_settings window_settings{
        "apeiron",
        SDL_INIT_VIDEO,
        settings.window_width,
        settings.window_height,
        settings.fullscreen,
        false,
        settings.msaa_samples,
        4,
        6,
        true
    };

    auto window_attributes = window.init(window_settings);

    settings.point_width = window_attributes.point_width;
    settings.point_height = window_attributes.point_height;
    settings.render_width = window_attributes.render_width;
    settings.render_height = window_attributes.render_height;

    std::cout << "Video driver: " << SDL_GetCurrentVideoDriver() << std::endl;
  }
  catch (const apeiron::engine::Error& e) {
    std::cerr << e.what() << std::endl;
    std::cin.ignore();
    return 1;
  }

  apeiron::example::World world{&settings};
  apeiron::example::Menu menu{window.sdl_window(), window.gl_context()};

  try {
    world.init();
    menu.init("#version 460");
    menu.setup(&settings);
  }
  catch (const apeiron::engine::Error& e) {
    std::cerr << e.what() << std::endl;
    std::cin.ignore();
    return 1;
  }

  auto frame_timer = [&settings, last_ticks = SDL_GetTicksNS()] mutable {
    auto current_ticks = SDL_GetTicksNS();
    auto elapsed_ticks = current_ticks - last_ticks;

    if (const auto target = 1'000'000'000ull / settings.max_fps; settings.limit_fps
        && elapsed_ticks < target) {
      SDL_DelayPrecise(target - elapsed_ticks);
      current_ticks = SDL_GetTicksNS();
      elapsed_ticks = current_ticks - last_ticks;
    }

    last_ticks = current_ticks;
    return elapsed_ticks;
  };

  std::vector<apeiron::engine::Event> engine_events;

  while (!settings.quit) {
    auto elapsed_ticks = frame_timer();  // May also delay and hence limits fps
    float delta_time_s = static_cast<float>(elapsed_ticks) / 1000'000'000.0f;
    auto time_s = static_cast<float>(SDL_GetTicks()) / 1000.0f;

    engine_events.clear();
    SDL_Event sdl_event;

    while (SDL_PollEvent(&sdl_event)) {
      if (settings.show_menu) {
        menu.process(&sdl_event);
      }

      apeiron::engine::add_input_event(sdl_event, engine_events, !menu.has_mouse());

      settings.quit = sdl_event.type == SDL_EVENT_QUIT;

      switch (sdl_event.type) {
        case SDL_EVENT_KEY_DOWN: {
          switch (sdl_event.key.key) {
            case SDLK_ESCAPE:
              settings.quit = true;
            break;
            case SDLK_F1:
              settings.show_menu = !settings.show_menu;

              if (settings.show_menu) {
                SDL_CaptureMouse(false);
                SDL_SetWindowRelativeMouseMode(window.sdl_window(), false);
              }
              else {
                SDL_GetRelativeMouseState(nullptr, nullptr);  // Prevent erroneous movement
                SDL_CaptureMouse(true);
                SDL_SetWindowRelativeMouseMode(window.sdl_window(), true);
              }
            break;
            case SDLK_F4:
              settings.wireframe = !settings.wireframe;
            break;
            default:;
          }
        }
        break;
        default:;
      }
    }

    auto input = apeiron::engine::get_input_state();

    world.update(time_s, delta_time_s, engine_events, &input);
    world.render();

    if (settings.show_menu) {
      menu.build(&settings, time_s);
      menu.render();
    }

    SDL_GL_SwapWindow(window.sdl_window());
  }

  apeiron::example::save_settings(settings, "settings.toml");

  return 0;
}

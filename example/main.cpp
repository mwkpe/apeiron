#include <iostream>

#include <SDL3/SDL.h>
#include <glad/glad.h>

#include "apeiron/engine/error.h"
#include "apeiron/engine/event.h"
#include "apeiron/engine/input.h"
#include "apeiron/engine/sdl_input.h"
#include "apeiron/engine/sdl_window_wrapper.h"
#include "apeiron/utility/dpi_scaling.h"

#include "example/settings.h"
#include "example/menu.h"
#include "example/world.h"


int main([[maybe_unused]] int argc, [[maybe_unused]] char* argv[])
{
  apeiron::utility::disable_dpi_scaling();

  apeiron::example::Settings settings;
  apeiron::engine::Sdl_window_wrapper window;

  try {
    settings = apeiron::example::load_settings("settings.toml");
    window.init("apeiron", SDL_INIT_VIDEO, 1280, 720, false, 4, 6, true, false,
        settings.msaa_samples);
  }
  catch (const apeiron::engine::Warning& w) {
    std::cout << w.what() << std::endl;
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

    if (auto target = 1'000'000'000ull / settings.max_fps; settings.limit_fps
        && elapsed_ticks < target) {
      SDL_DelayPrecise(target - elapsed_ticks);
      current_ticks = SDL_GetTicksNS();
      elapsed_ticks = current_ticks - last_ticks;
    }

    last_ticks = current_ticks;
    return elapsed_ticks;
  };

  std::vector<apeiron::engine::Event> events;

  while (!settings.quit) {
    auto elapsed_ticks = frame_timer();  // May also delay and hence limits fps
    float delta_time_s = static_cast<float>(elapsed_ticks) / 1000'000'000.0f;
    auto time_s = static_cast<float>(SDL_GetTicks()) / 1000.0f;

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
    world.update(time_s, delta_time_s, events, &input);
    events.clear();

    glCullFace(GL_BACK);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);

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

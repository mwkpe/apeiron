#include <iostream>

#include <SDL3/SDL.h>

#include "apeiron/engine/error.h"
#include "apeiron/engine/event.h"
#include "apeiron/engine/input.h"
#include "apeiron/engine/sdl_input.h"

#include "apeiron/opengl/window.h"

#include "example/settings.h"
#include "example/menu.h"
#include "example/world.h"


int main([[maybe_unused]] int argc, [[maybe_unused]] char* argv[])
{
  apeiron::example::Settings settings;
  apeiron::opengl::Window window;

  try {
    settings = apeiron::example::load_settings("settings.toml");
  }
  catch (const apeiron::engine::Warning& w) {
    std::cout << w.what() << std::endl;
  }

  const int gl_major = 3;
  const int gl_minor = 3;

  try {
    window.init({
        .title = "apeiron",
        .init_flags = SDL_INIT_VIDEO,
        .width = settings.window_width,
        .height = settings.window_height,
        .ignore_scaling = true,
        .resizable = true,
        .fullscreen = settings.fullscreen,
        .vsync = settings.vsync,
        .msaa_samples = settings.msaa_samples,
        .gl_major = gl_major,
        .gl_minor = gl_minor,
        .gl_core = true
    });

    auto a = window.attributes();

    settings.logical_width = a.logical_width;
    settings.logical_height = a.logical_height;
    settings.render_width = a.render_width;
    settings.render_height = a.render_height;
    settings.video_driver = SDL_GetCurrentVideoDriver();
  }
  catch (const apeiron::engine::Error& e) {
    std::cerr << e.what() << '\n';
    std::cerr << "Press key to continue..." << std::endl;
    std::cin.ignore();
    return 1;
  }

  apeiron::example::World world{&settings};
  apeiron::example::Menu menu{window.sdl_window(), window.gl_context()};

  try {
    world.init();
    menu.init(gl_major, gl_minor);
    menu.setup(&settings);
  }
  catch (const apeiron::engine::Error& e) {
    std::cerr << e.what() << '\n';
    std::cerr << "Press key to continue..." << std::endl;
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
    bool window_changed = false;

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
        case SDL_EVENT_WINDOW_PIXEL_SIZE_CHANGED:
        case SDL_EVENT_WINDOW_RESIZED:
        case SDL_EVENT_WINDOW_DISPLAY_SCALE_CHANGED:
          window_changed = true;
        default:;
      }
    }

    if (window_changed) {
      auto a = window.attributes();
      settings.logical_width = a.logical_width;
      settings.logical_height = a.logical_height;
      settings.render_width = a.render_width;
      settings.render_height = a.render_height;

      world.update_view();
      window_changed = false;
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

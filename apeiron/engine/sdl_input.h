#ifndef APEIRON_ENGINE_SDL_INPUT_H
#define APEIRON_ENGINE_SDL_INPUT_H


#include <cstdint>
#include <SDL3/SDL.h>
#include "apeiron/engine/input.h"


namespace apeiron::engine {


inline apeiron::engine::Input get_input_state()
{
  apeiron::engine::Input input;
  const bool* kb_state = SDL_GetKeyboardState(nullptr);

  input.forward = kb_state[SDL_SCANCODE_UP] || kb_state[SDL_SCANCODE_E];
  input.backward = kb_state[SDL_SCANCODE_DOWN] || kb_state[SDL_SCANCODE_D];
  input.left = kb_state[SDL_SCANCODE_LEFT] || kb_state[SDL_SCANCODE_S];
  input.right = kb_state[SDL_SCANCODE_RIGHT] || kb_state[SDL_SCANCODE_F];

  input.action1 = kb_state[SDL_SCANCODE_LSHIFT];
  input.action2 = kb_state[SDL_SCANCODE_H];

  auto mouse_state = SDL_GetMouseState(&input.mouse_x_abs, &input.mouse_y_abs);
  SDL_GetRelativeMouseState(&input.mouse_x_rel, &input.mouse_y_rel);
  input.mouse_y_rel = -input.mouse_y_rel;  // Make mouse up correspond to camera pitch up
  input.mouse_left = mouse_state & SDL_BUTTON_MASK(SDL_BUTTON_LEFT);
  input.mouse_middle = mouse_state & SDL_BUTTON_MASK(SDL_BUTTON_MIDDLE);
  input.mouse_right =  mouse_state & SDL_BUTTON_MASK(SDL_BUTTON_RIGHT);

  return input;
}


inline apeiron::engine::Mouse_button get_mouse_button(std::uint8_t button)
{
  using namespace apeiron::engine;

  switch (button) {
    case SDL_BUTTON_LEFT: return Mouse_button::Left;
    case SDL_BUTTON_MIDDLE: return Mouse_button::Middle;
    case SDL_BUTTON_RIGHT: return Mouse_button::Right;
    case SDL_BUTTON_X1: return Mouse_button::Side1;
    case SDL_BUTTON_X2: return Mouse_button::Side2;
    default:;
  }

  return Mouse_button::Unknown;
}


inline apeiron::engine::Gamepad_button get_controller_button(SDL_GamepadButton button)
{
  using namespace apeiron::engine;

  switch (button) {
    case SDL_GAMEPAD_BUTTON_SOUTH: return Gamepad_button::South;
    case SDL_GAMEPAD_BUTTON_EAST: return Gamepad_button::East;
    case SDL_GAMEPAD_BUTTON_WEST: return Gamepad_button::West;
    case SDL_GAMEPAD_BUTTON_NORTH: return Gamepad_button::North;
    case SDL_GAMEPAD_BUTTON_BACK: return Gamepad_button::Back;
    case SDL_GAMEPAD_BUTTON_GUIDE: return Gamepad_button::Guide;
    case SDL_GAMEPAD_BUTTON_START: return Gamepad_button::Start;
    case SDL_GAMEPAD_BUTTON_LEFT_STICK: return Gamepad_button::Left_stick;
    case SDL_GAMEPAD_BUTTON_RIGHT_STICK: return Gamepad_button::Right_stick;
    case SDL_GAMEPAD_BUTTON_LEFT_SHOULDER: return Gamepad_button::Left_shoulder;
    case SDL_GAMEPAD_BUTTON_RIGHT_SHOULDER: return Gamepad_button::Right_shoulder;
    case SDL_GAMEPAD_BUTTON_DPAD_UP: return Gamepad_button::Dpad_up;
    case SDL_GAMEPAD_BUTTON_DPAD_DOWN: return Gamepad_button::Dpad_down;
    case SDL_GAMEPAD_BUTTON_DPAD_LEFT: return Gamepad_button::Dpad_left;
    case SDL_GAMEPAD_BUTTON_DPAD_RIGHT: return Gamepad_button::Dpad_right;
    case SDL_GAMEPAD_BUTTON_MISC1: return Gamepad_button::Misc1;
    case SDL_GAMEPAD_BUTTON_RIGHT_PADDLE1: return Gamepad_button::Right_paddle1;
    case SDL_GAMEPAD_BUTTON_LEFT_PADDLE1: return Gamepad_button::Left_paddle1;
    case SDL_GAMEPAD_BUTTON_RIGHT_PADDLE2: return Gamepad_button::Right_paddle2;
    case SDL_GAMEPAD_BUTTON_LEFT_PADDLE2: return Gamepad_button::Left_paddle2;
    case SDL_GAMEPAD_BUTTON_TOUCHPAD: return Gamepad_button::Touchpad;
    case SDL_GAMEPAD_BUTTON_MISC2: return Gamepad_button::Misc2;
    case SDL_GAMEPAD_BUTTON_MISC3: return Gamepad_button::Misc3;
    case SDL_GAMEPAD_BUTTON_MISC4: return Gamepad_button::Misc4;
    case SDL_GAMEPAD_BUTTON_MISC5: return Gamepad_button::Misc5;
    case SDL_GAMEPAD_BUTTON_MISC6: return Gamepad_button::Misc6;
    default:;
  }

  return Gamepad_button::Unknown;
}


inline apeiron::engine::Gamepad_axis get_controller_axis(SDL_GamepadAxis axis)
{
  using namespace apeiron::engine;

  switch (axis) {
    case SDL_GAMEPAD_AXIS_LEFTX: return Gamepad_axis::Left_x;
    case SDL_GAMEPAD_AXIS_LEFTY: return Gamepad_axis::Left_y;
    case SDL_GAMEPAD_AXIS_RIGHTX: return Gamepad_axis::Right_x;
    case SDL_GAMEPAD_AXIS_RIGHTY: return Gamepad_axis::Right_y;
    case SDL_GAMEPAD_AXIS_LEFT_TRIGGER: return Gamepad_axis::Left_trigger;
    case SDL_GAMEPAD_AXIS_RIGHT_TRIGGER: return Gamepad_axis::Right_trigger;
    default:;
  }

  return Gamepad_axis::Unknown;
}


}  // namespace apeiron::engine


#endif  // APEIRON_ENGINE_SDL_INPUT_H

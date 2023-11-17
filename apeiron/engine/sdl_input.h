#ifndef APEIRON_ENGINE_SDL_INPUT_H
#define APEIRON_ENGINE_SDL_INPUT_H


#include <cstdint>
#include "SDL2/SDL.h"
#include "apeiron/engine/input.h"


namespace apeiron::engine {


inline apeiron::engine::Input get_input_state()
{
  apeiron::engine::Input input;
  const std::uint8_t* kb_state = SDL_GetKeyboardState(nullptr);

  input.forward = kb_state[SDL_SCANCODE_UP] || kb_state[SDL_SCANCODE_E];
  input.backward = kb_state[SDL_SCANCODE_DOWN] || kb_state[SDL_SCANCODE_D];
  input.left = kb_state[SDL_SCANCODE_LEFT] || kb_state[SDL_SCANCODE_S];
  input.right = kb_state[SDL_SCANCODE_RIGHT] || kb_state[SDL_SCANCODE_F];

  input.action1 = kb_state[SDL_SCANCODE_LSHIFT];
  input.action2 = kb_state[SDL_SCANCODE_H];

  auto mouse_state = SDL_GetMouseState(&input.mouse_x_abs, &input.mouse_y_abs);
  SDL_GetRelativeMouseState(&input.mouse_x_rel, &input.mouse_y_rel);
  input.mouse_y_rel = -input.mouse_y_rel;  // Make mouse up correspond to camera pitch up
  input.mouse_left = mouse_state & SDL_BUTTON(SDL_BUTTON_LEFT);
  input.mouse_middle = mouse_state & SDL_BUTTON(SDL_BUTTON_MIDDLE);
  input.mouse_right =  mouse_state & SDL_BUTTON(SDL_BUTTON_RIGHT);

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


inline apeiron::engine::Controller_button get_controller_button(std::uint8_t button)
{
  using namespace apeiron::engine;

  switch (button) {
    case SDL_CONTROLLER_BUTTON_A: return Controller_button::A;
    case SDL_CONTROLLER_BUTTON_B: return Controller_button::B;
    case SDL_CONTROLLER_BUTTON_X: return Controller_button::X;
    case SDL_CONTROLLER_BUTTON_Y: return Controller_button::Y;
    case SDL_CONTROLLER_BUTTON_BACK: return Controller_button::Back;
    case SDL_CONTROLLER_BUTTON_GUIDE: return Controller_button::Guide;
    case SDL_CONTROLLER_BUTTON_START: return Controller_button::Start;
    case SDL_CONTROLLER_BUTTON_LEFTSTICK: return Controller_button::Left_stick;
    case SDL_CONTROLLER_BUTTON_RIGHTSTICK: return Controller_button::Right_stick;
    case SDL_CONTROLLER_BUTTON_LEFTSHOULDER: return Controller_button::Left_shoulder;
    case SDL_CONTROLLER_BUTTON_RIGHTSHOULDER: return Controller_button::Right_shoulder;
    case SDL_CONTROLLER_BUTTON_DPAD_UP: return Controller_button::Dpad_up;
    case SDL_CONTROLLER_BUTTON_DPAD_DOWN: return Controller_button::Dpad_down;
    case SDL_CONTROLLER_BUTTON_DPAD_LEFT: return Controller_button::Dpad_left;
    case SDL_CONTROLLER_BUTTON_DPAD_RIGHT: return Controller_button::Dpad_right;
    case SDL_CONTROLLER_BUTTON_MISC1: return Controller_button::Misc1;
    case SDL_CONTROLLER_BUTTON_PADDLE1: return Controller_button::Paddle1;
    case SDL_CONTROLLER_BUTTON_PADDLE2: return Controller_button::Paddle2;
    case SDL_CONTROLLER_BUTTON_PADDLE3: return Controller_button::Paddle3;
    case SDL_CONTROLLER_BUTTON_PADDLE4: return Controller_button::Paddle4;
    case SDL_CONTROLLER_BUTTON_TOUCHPAD: return Controller_button::Touchpad;
    default:;
  }

  return Controller_button::Unknown;
}


inline apeiron::engine::Controller_axis get_controller_axis(std::uint8_t axis)
{
  using namespace apeiron::engine;

  switch (axis) {
    case SDL_CONTROLLER_AXIS_LEFTX: return Controller_axis::Left_x;
    case SDL_CONTROLLER_AXIS_LEFTY: return Controller_axis::Left_y;
    case SDL_CONTROLLER_AXIS_RIGHTX: return Controller_axis::Right_x;
    case SDL_CONTROLLER_AXIS_RIGHTY: return Controller_axis::Right_y;
    case SDL_CONTROLLER_AXIS_TRIGGERLEFT: return Controller_axis::Trigger_left;
    case SDL_CONTROLLER_AXIS_TRIGGERRIGHT: return Controller_axis::Trigger_right;
    default:;
  }

  return Controller_axis::Unknown;
}


}  // namespace apeiron::engine


#endif  // APEIRON_ENGINE_SDL_INPUT_H

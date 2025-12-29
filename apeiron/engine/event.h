#ifndef APEIRON_ENGINE_EVENT_H
#define APEIRON_ENGINE_EVENT_H


#include <cstdint>
#include <variant>
#include <vector>


namespace apeiron::engine {


enum class Mouse_button : std::uint8_t
{ 
  Left,
  Middle,
  Right,
  Side1,
  Side2,
  Unknown
};

enum class Gamepad_button : std::uint8_t
{
  South,
  East,
  West,
  North,
  Back,
  Guide,
  Start,
  Left_stick,
  Right_stick,
  Left_shoulder,
  Right_shoulder,
  Dpad_up,
  Dpad_down,
  Dpad_left,
  Dpad_right,
  Misc1,
  Right_paddle1,
  Left_paddle1,
  Right_paddle2,
  Left_paddle2,
  Touchpad,
  Misc2,
  Misc3,
  Misc4,
  Misc5,
  Misc6,
  Unknown
};

enum class Gamepad_axis : std::uint8_t
{
  Left_x,
  Left_y,
  Right_x,
  Right_y,
  Left_trigger,
  Right_trigger,
  Unknown
};


struct Key_down_event
{
  std::int32_t keycode;
  std::uint16_t keymod;
};

struct Key_up_event
{
  std::int32_t keycode;
  std::uint16_t keymod;
};

struct Mouse_motion_event
{
  float x;
  float y;
  float x_rel;
  float y_rel;
};

struct Mouse_button_down_event
{
  Mouse_button button;
  float x;
  float y; 
};

struct Mouse_button_up_event
{
  Mouse_button button;
  float x;
  float y; 
};

struct Mouse_wheel_event
{
  float x;
  float y;
};

struct Gamepad_button_down_event
{
  Gamepad_button button;
};

struct Gamepad_button_up_event
{
  Gamepad_button button;
};

struct Gamepad_axis_motion_event
{
  Gamepad_axis axis;
  float value;
};


using Event = std::variant<
    Key_down_event,
    Key_up_event,
    Mouse_motion_event,
    Mouse_button_down_event,
    Mouse_button_up_event,
    Mouse_wheel_event,
    Gamepad_button_down_event,
    Gamepad_button_up_event,
    Gamepad_axis_motion_event>;

using Event_queue = std::vector<Event>;


}  // namespace apeiron::engine


#endif  // APEIRON_ENGINE_EVENT_H

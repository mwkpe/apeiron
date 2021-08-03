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

enum class Controller_button : std::uint8_t
{
  A,
  B,
  X,
  Y,
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
  Paddle1,
  Paddle2,
  Paddle3,
  Paddle4,
  Touchpad,
  Unknown
};

enum class Controller_axis : std::uint8_t
{
  Left_x,
  Left_y,
  Right_x,
  Right_y,
  Trigger_left,
  Trigger_right,
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
  std::int32_t x;
  std::int32_t y;
  std::int32_t x_rel;
  std::int32_t y_rel;
};

struct Mouse_button_down_event
{
  Mouse_button button;
  std::int32_t x;
  std::int32_t y; 
};

struct Mouse_button_up_event
{
  Mouse_button button;
  std::int32_t x;
  std::int32_t y; 
};

struct Mouse_wheel_event
{
  std::int32_t x;
  std::int32_t y;
};

struct Controller_button_down_event
{
  Controller_button button;
};

struct Controller_button_up_event
{
  Controller_button button;
};

struct Controller_axis_motion_event
{
  Controller_axis axis;
  float value;
};


using Event = std::variant<
    Key_down_event,
    Key_up_event,
    Mouse_motion_event,
    Mouse_button_down_event,
    Mouse_button_up_event,
    Mouse_wheel_event,
    Controller_button_down_event,
    Controller_button_up_event,
    Controller_axis_motion_event>;

using Event_queue = std::vector<Event>;


}  // namespace apeiron::engine


#endif  // APEIRON_ENGINE_EVENT_H

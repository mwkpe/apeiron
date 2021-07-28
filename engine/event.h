#ifndef APEIRON_ENGINE_EVENT_H
#define APEIRON_ENGINE_EVENT_H


#include <cstdint>
#include <variant>
#include <vector>


namespace apeiron::engine {


enum class Mouse_button : std::uint8_t  { Unknown, Left, Middle, Right, Side1, Side2 };


struct Key_down_event
{
  int keycode;
  int keymod;
};


struct Key_up_event
{
  int keycode;
  int keymod;
};


struct Mouse_motion_event
{
  std::int32_t x;
  std::int32_t y;
  std::int32_t x_rel;
  std::int32_t y_rel;
};


struct Mouse_button_up_event
{
  Mouse_button button;
  std::int32_t x;
  std::int32_t y; 
};


struct Mouse_button_down_event
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


using Event = std::variant<
    Key_down_event,
    Key_up_event,
    Mouse_motion_event,
    Mouse_button_up_event,
    Mouse_button_down_event,
    Mouse_wheel_event>;

using Event_queue = std::vector<Event>;


}  // namespace apeiron::engine


#endif  // APEIRON_ENGINE_EVENT_H

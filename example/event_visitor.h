#ifndef APEIRON_EVENT_VISITOR_H
#define APEIRON_EVENT_VISITOR_H


#include "engine/event.h"


namespace apeiron::example {


class World;


class Event_visitor final
{
public:
  explicit Event_visitor(World& world) : world_{world} {};
  void operator()(const apeiron::engine::Mouse_button_down_event& event);
  void operator()(const apeiron::engine::Mouse_button_up_event& event);
  void operator()(const apeiron::engine::Mouse_wheel_event& event);

private:
  World& world_;
};


}  // namespace apeiron::example


#endif  // APEIRON_EVENT_VISITOR_H

#include "event_visitor.h"


#include "world.h"


using namespace apeiron::engine;
using namespace apeiron::example;


void Event_visitor::operator()([[maybe_unused]] const Mouse_button_down_event& event)
{
  world_.handle_mouse_click(event.x, event.y);
}


void Event_visitor::operator()([[maybe_unused]] const Mouse_button_up_event& event)
{
}


void Event_visitor::operator()([[maybe_unused]] const Mouse_wheel_event& event)
{
}

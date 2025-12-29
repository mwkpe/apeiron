#ifndef APEIRON_ENGINE_INPUT_H
#define APEIRON_ENGINE_INPUT_H


namespace apeiron::engine {


// Generic input for convenience
struct Input
{
  bool forward = false;
  bool backward = false;
  bool left = false;
  bool right = false;
  bool action1 = false;
  bool action2 = false;
  bool action3 = false;
  bool mouse_left = false;
  bool mouse_middle = false;
  bool mouse_right = false;
  bool mouse_side1 = false;
  bool mouse_side2 = false;
  float mouse_x_abs = 0.0f;
  float mouse_x_rel = 0.0f;
  float mouse_y_abs = 0.0f;
  float mouse_y_rel = 0.0f;
};


}  // namespace apeiron::engine


#endif  // APEIRON_ENGINE_INPUT_H

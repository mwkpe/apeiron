#ifndef APEIRON_ENGINE_INPUT_H
#define APEIRON_ENGINE_INPUT_H


namespace apeiron::engine {


struct Input
{
  bool forward = false;
  bool backward = false;
  bool left = false;
  bool right = false;
  int mouse_x_abs = 0;
  int mouse_x_rel = 0;
  int mouse_y_abs = 0;
  int mouse_y_rel = 0;
};


}  // namespace apeiron::engine


#endif  // APEIRON_ENGINE_INPUT_H

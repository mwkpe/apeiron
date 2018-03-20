#ifndef APEIRON_INPUT_H
#define APEIRON_INPUT_H


namespace apeiron {


struct Input
{
  bool forward;
  bool backward;
  bool left;
  bool right;
  int mouse_x_abs;
  int mouse_x_rel;
  int mouse_y_abs;
  int mouse_y_rel;
};


}  // namespace apeiron


#endif  // APEIRON_INPUT_H

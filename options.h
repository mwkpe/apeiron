#ifndef APEIRON_OPTIONS_H
#define APEIRON_OPTIONS_H


namespace apeiron {


struct Options
{
  bool quit = false;
  bool show_gui = false;
  bool wireframe = true;
  bool strobe = false;
  bool autorotate = true;
  float rotation_angle = false;
};


}  // namespace apeiron


#endif  //APEIRON_OPTIONS_H

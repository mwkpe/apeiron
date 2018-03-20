#ifndef APEIRON_OPTIONS_H
#define APEIRON_OPTIONS_H


namespace apeiron {


struct Options
{
  bool quit = false;
  bool show_gui = true;
  bool autorotate = true;
  bool wireframe = true;
  bool strobe = false;
  float velocity = 2.0f;
  float sensitivity = 0.05f;
};


}  // namespace apeiron


#endif  //APEIRON_OPTIONS_H

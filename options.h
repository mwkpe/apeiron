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
  bool limit_fps = true;
  int max_fps = 120;
  float velocity = 2.0f;
  float sensitivity = 0.02f;
};


}  // namespace apeiron


#endif  //APEIRON_OPTIONS_H

#include "menu.h"


#include "GL/glew.h"
#include "imgui/imgui.h"
#include "engine/color.h"


namespace {


void set_style(ImGuiStyle& style)
{
  style.WindowPadding = ImVec2{8, 8};
  style.WindowRounding = 0.0f;
  style.WindowBorderSize = 0.0f;
  style.FramePadding = ImVec2{3, 3};
  style.FrameRounding = 0.0f;
  style.FrameBorderSize = 0.0f;
  style.ItemSpacing = ImVec2{12, 8};
  style.ItemInnerSpacing = ImVec2{8, 6};
  style.IndentSpacing = 25.0f;
  style.ScrollbarSize = 15.0f;
  style.ScrollbarRounding = 9.0f;
  style.GrabMinSize = 5.0f;
  style.GrabRounding = 5.0f;

  ImVec4 almostblack{0.03f, 0.03f, 0.03f, 1.0f};
  ImVec4 blackglass{0.05f, 0.05f, 0.05f, 0.9f};
  ImVec4 darkgrey{0.15f, 0.15f, 0.15f, 0.9f};
  ImVec4 grey{0.2f, 0.2f, 0.2f, 0.9f};
  ImVec4 lightgrey{0.4f, 0.4f, 0.4f, 0.9f};

  style.Colors[ImGuiCol_WindowBg] = blackglass;
  style.Colors[ImGuiCol_FrameBg] = darkgrey;
  style.Colors[ImGuiCol_FrameBgHovered] = grey;
  style.Colors[ImGuiCol_FrameBgActive] = grey;
  style.Colors[ImGuiCol_TextDisabled] = grey;
  style.Colors[ImGuiCol_TitleBg] = darkgrey;
  style.Colors[ImGuiCol_TitleBgCollapsed] = darkgrey;
  style.Colors[ImGuiCol_TitleBgActive] = grey;
  style.Colors[ImGuiCol_ResizeGrip] = darkgrey;
  style.Colors[ImGuiCol_ResizeGripHovered] = lightgrey;
  style.Colors[ImGuiCol_SliderGrab] = almostblack;
  style.Colors[ImGuiCol_SliderGrabActive] = lightgrey;
  style.Colors[ImGuiCol_Button] = darkgrey;
  style.Colors[ImGuiCol_ButtonHovered] = grey;
  style.Colors[ImGuiCol_ButtonActive] = lightgrey;
}


void set_main_color(ImGuiStyle& style, ImVec4 color)
{
  style.Colors[ImGuiCol_Border] = color;
  style.Colors[ImGuiCol_Text] = color;
  style.Colors[ImGuiCol_CheckMark] = color;
  style.Colors[ImGuiCol_ResizeGripActive] = color;
}


}  // namespace


void apeiron::example::Menu::setup(example::Options* options)
{
  ImGui::StyleColorsDark();
  set_style(ImGui::GetStyle());
  const auto& color = options->main_color;
  set_main_color(ImGui::GetStyle(), ImVec4{color.r, color.g, color.b, color.a});
}


void apeiron::example::Menu::build(example::Options* options, float time)
{
  auto& io = ImGui::GetIO();

  create_frame();
  {
    ImGui::Begin("Debug view (F1)");
    ImGui::Text("Time: %.2f", time);
    ImGui::Text("Framerate: %.0f fps", io.Framerate);
    ImGui::Text("Frametime: %.3f ms", 1000.0f / io.Framerate);
    ImGui::Checkbox("Limit framerate", &options->limit_fps);
    ImGui::SliderInt("Max FPS", &options->max_fps, 30, 240);
    ImGui::Text("World");
    ImGui::Checkbox("Lighting", &options->lighting);
    ImGui::Checkbox("Show Light Position", &options->show_light);
    ImGui::SliderFloat("Light distance (m)", &options->light_distance, -25.0f, 25.0f);
    ImGui::SliderInt("Cyliner detail", &options->cylinder_points, 1, 64);
    ImGui::SliderFloat("Cyliner distance (m)", &options->cylinder_distance, 0.0f, 100.0f);
    ImGui::SliderFloat("Cyliner rev/s", &options->cylinder_revs, 0.1f, 1.0f);
    ImGui::Checkbox("Autorotate", &options->autorotate);
    ImGui::Checkbox("Wireframe (F2)", &options->wireframe);
    ImGui::Checkbox("Arr!", &options->pirate_mode);
    ImGui::Text("Camera");
    ImGui::SliderFloat("Velocity (m/s)", &options->velocity, 0.0f, 20.0f);
    ImGui::SliderFloat("Sensitivity", &options->sensitivity, 0.0f, 0.1f);
    ImGui::Text("Color");
    if (ImGui::Button("White")) {
      set_main_color(ImGui::GetStyle(), ImVec4{0.9f, 0.9f, 0.9f, 1.0f});
      options->main_color = engine::Color{0.9f, 0.9f, 0.9f, 1.0f};
    }
    ImGui::SameLine();
    if (ImGui::Button("Orange")) {
      set_main_color(ImGui::GetStyle(), ImVec4{0.996, 0.647, 0.0f, 1.0f});
      options->main_color = engine::Color{0.996, 0.647, 0.0f, 1.0f};
    }
    ImGui::SameLine();
    if (ImGui::Button("Pink")) {
      set_main_color(ImGui::GetStyle(), ImVec4{0.988f, 0.176f, 0.584f, 1.0f});
      options->main_color = engine::Color{0.988f, 0.176f, 0.584f, 1.0f};
    }
    ImGui::SameLine();
    if (ImGui::Button("Blue")) {
      set_main_color(ImGui::GetStyle(), ImVec4{0.2f, 0.905f, 0.968f, 1.0f});
      options->main_color = engine::Color{0.2f, 0.905f, 0.968f, 1.0f};
    }
    ImGui::SameLine();
    if (ImGui::Button("Green")) {
      set_main_color(ImGui::GetStyle(), ImVec4{0.0f, 1.0f, 0.25f, 1.0f});
      options->main_color = engine::Color{0.0f, 1.0f, 0.25f, 1.0f};
    }
    if (ImGui::Button("Quit"))
      options->quit = true;
    ImGui::End();
  }
}

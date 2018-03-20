#include "gui.h"


#include "GL/glew.h"
#include "imgui/imgui.h"
#include "imgui/examples/sdl_opengl3_example/imgui_impl_sdl_gl3.h"
#include "color.h"


namespace {


void set_style(ImGuiStyle& style)
{
  style.WindowPadding = ImVec2{8, 8};
  style.WindowRounding = 5.0f;
  style.FramePadding = ImVec2{3, 3};
  style.FrameRounding = 0.0f;
  style.ItemSpacing = ImVec2{12, 8};
  style.ItemInnerSpacing = ImVec2{8, 6};
  style.IndentSpacing = 25.0f;
  style.ScrollbarSize = 15.0f;
  style.ScrollbarRounding = 9.0f;
  style.GrabMinSize = 5.0f;
  style.GrabRounding = 5.0f;

  ImVec4 almostblack{0.03f, 0.03f, 0.03f, 1.0f};
  ImVec4 blackglass{0.1f, 0.1f, 0.1f, 0.85f};
  ImVec4 fuchsia{0.9f, 0.0f, 0.9f, 1.0f};
  ImVec4 orange{0.996, 0.647, 0.0f, 1.0f};
  ImVec4 turquoise{0.2f, 0.905f, 0.968f, 1.0f};
  ImVec4 darkgrey{0.2f, 0.2f, 0.2f, 0.8f};
  ImVec4 grey{0.25f, 0.25f, 0.25f, 0.8f};
  ImVec4 lightgrey{0.4f, 0.4f, 0.4f, 0.8f};

  style.Colors[ImGuiCol_WindowBg] = blackglass;
  style.Colors[ImGuiCol_Border] = orange;
  style.Colors[ImGuiCol_FrameBg] = darkgrey;
  style.Colors[ImGuiCol_FrameBgHovered] = grey;
  style.Colors[ImGuiCol_FrameBgActive] = grey;
  style.Colors[ImGuiCol_Text] = orange;
  style.Colors[ImGuiCol_TextDisabled] = grey;
  style.Colors[ImGuiCol_TitleBg] = blackglass;
  style.Colors[ImGuiCol_TitleBgCollapsed] = blackglass;
  style.Colors[ImGuiCol_TitleBgActive] = grey;
  style.Colors[ImGuiCol_ResizeGrip] = almostblack;
  style.Colors[ImGuiCol_ResizeGripHovered] = lightgrey;
  style.Colors[ImGuiCol_ResizeGripActive] = orange;
  style.Colors[ImGuiCol_SliderGrab] = almostblack;
  style.Colors[ImGuiCol_SliderGrabActive] = lightgrey;
  style.Colors[ImGuiCol_Button] = darkgrey;
  style.Colors[ImGuiCol_ButtonHovered] = grey;
  style.Colors[ImGuiCol_ButtonActive] = lightgrey;
  style.Colors[ImGuiCol_CheckMark] = orange;
}


void set_main_color(ImGuiStyle& style, ImVec4 color)
{
  style.Colors[ImGuiCol_Border] = color;
  style.Colors[ImGuiCol_Text] = color;
  style.Colors[ImGuiCol_CheckMark] = color;
  style.Colors[ImGuiCol_ResizeGripActive] = color;
}


}  // namespace


void apeiron::Gui::init()
{
  ImGui::CreateContext();
  ImGui_ImplSdlGL3_Init(window_);
  ImGui::StyleColorsDark();
  set_style(ImGui::GetStyle());
  const auto& color = options_->main_color;
  set_main_color(ImGui::GetStyle(), ImVec4{color.r, color.g, color.b, color.a});
}


void apeiron::Gui::process(SDL_Event* event)
{
  ImGui_ImplSdlGL3_ProcessEvent(event);
}


void apeiron::Gui::render(float time)
{
  auto& io = ImGui::GetIO();

  ImGui_ImplSdlGL3_NewFrame(window_);
  {
    ImGui::Begin("Debug view (F1)");
    ImGui::Text("Time: %.2f", time);
    ImGui::Text("Framerate: %.0f fps", io.Framerate);
    ImGui::Text("Frametime: %.3f ms", 1000.0f / io.Framerate);
    ImGui::Checkbox("Limit framerate", &options_->limit_fps);
    ImGui::SliderInt("Max FPS", &options_->max_fps, 30, 240);
    ImGui::SliderInt("Cyliner detail", &options_->cylinder_points, 4, 64);
    ImGui::Checkbox("Autorotate", &options_->autorotate);
    ImGui::Checkbox("Wireframe (F2)", &options_->wireframe);
    ImGui::Checkbox("Strobe", &options_->strobe);
    ImGui::SliderFloat("Velocity", &options_->velocity, 0.0f, 5.0f);
    ImGui::SliderFloat("Sensitivity", &options_->sensitivity, 0.0f, 0.1f);
    if (ImGui::Button("Orange")) {
      set_main_color(ImGui::GetStyle(), ImVec4{0.996, 0.647, 0.0f, 1.0f});
      options_->main_color = Color{0.996, 0.647, 0.0f, 1.0f};
    }
    ImGui::SameLine();
    if (ImGui::Button("Pink")) {
      set_main_color(ImGui::GetStyle(), ImVec4{0.988f, 0.176f, 0.584f, 1.0f});
      options_->main_color = Color{0.988f, 0.176f, 0.584f, 1.0f};
    }
    ImGui::SameLine();
    if (ImGui::Button("Blue")) {
      set_main_color(ImGui::GetStyle(), ImVec4{0.2f, 0.905f, 0.968f, 1.0f});
      options_->main_color = Color{0.2f, 0.905f, 0.968f, 1.0f};
    }
    if (ImGui::Button("Quit"))
      options_->quit = true;
    ImGui::End();
  }

  glViewport(0, 0, static_cast<int>(io.DisplaySize.x), static_cast<int>(io.DisplaySize.y));
  ImGui::Render();
  ImGui_ImplSdlGL3_RenderDrawData(ImGui::GetDrawData());
}

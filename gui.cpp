#include "gui.h"


#include "GL/glew.h"
#include "imgui/imgui.h"
#include "imgui/examples/sdl_opengl3_example/imgui_impl_sdl_gl3.h"


namespace {


struct Color
{
  float r;
  float g;
  float b;
  float a;
};


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

  Color blackglass{0.1f, 0.1f, 0.1f, 0.85f};
  Color fuchsia{0.9f, 0.0f, 0.9f, 1.0f};
  Color turquoise{0.2f, 0.905f, 0.968f, 1.0f};
  Color darkgrey{0.2f, 0.2f, 0.2f, 0.8f};
  Color grey{0.25f, 0.25f, 0.25f, 0.8f};
  Color lightgrey{0.3f, 0.3f, 0.3f, 0.8f};

  style.Colors[ImGuiCol_WindowBg] = ImVec4{blackglass.r, blackglass.g, blackglass.b, blackglass.a};
  style.Colors[ImGuiCol_Border] = ImVec4{fuchsia.r, fuchsia.g, fuchsia.b, fuchsia.a};
  style.Colors[ImGuiCol_FrameBg] = ImVec4{darkgrey.r, darkgrey.g, darkgrey.b, darkgrey.a};
  style.Colors[ImGuiCol_FrameBgHovered] = ImVec4{grey.r, grey.g, grey.b, grey.a};
  style.Colors[ImGuiCol_FrameBgActive] = ImVec4{grey.r, grey.g, grey.b, grey.a};
  style.Colors[ImGuiCol_Text] = ImVec4{fuchsia.r, fuchsia.g, fuchsia.b, fuchsia.a};
  style.Colors[ImGuiCol_TextDisabled] = ImVec4{grey.r, grey.g, grey.b, grey.a};
  style.Colors[ImGuiCol_TitleBg] = ImVec4{blackglass.r, blackglass.g, blackglass.b, blackglass.a};
  style.Colors[ImGuiCol_TitleBgCollapsed] = ImVec4{blackglass.r, blackglass.g, blackglass.b, blackglass.a};
  style.Colors[ImGuiCol_TitleBgActive] = ImVec4{grey.r, grey.g, grey.b, grey.a};
  style.Colors[ImGuiCol_ResizeGrip] = ImVec4{darkgrey.r, darkgrey.g, darkgrey.b, darkgrey.a};
  style.Colors[ImGuiCol_ResizeGripHovered] = ImVec4{turquoise.r, turquoise.g, turquoise.b, turquoise.a};
  style.Colors[ImGuiCol_ResizeGripActive] = ImVec4{fuchsia.r, fuchsia.g, fuchsia.b, fuchsia.a};
  style.Colors[ImGuiCol_SliderGrab] = ImVec4{lightgrey.r, lightgrey.g, lightgrey.b, lightgrey.a};
  style.Colors[ImGuiCol_SliderGrabActive] = ImVec4{turquoise.r, turquoise.g, turquoise.b, turquoise.a};
  style.Colors[ImGuiCol_Button] = ImVec4{darkgrey.r, darkgrey.g, darkgrey.b, darkgrey.a};
  style.Colors[ImGuiCol_ButtonHovered] = ImVec4{grey.r, grey.g, grey.b, grey.a};
  style.Colors[ImGuiCol_ButtonActive] = ImVec4{lightgrey.r, lightgrey.g, lightgrey.b, lightgrey.a};
  style.Colors[ImGuiCol_CheckMark] = ImVec4{fuchsia.r, fuchsia.g, fuchsia.b, fuchsia.a};
}


}  // namespace


void apeiron::Gui::init()
{
  ImGui::CreateContext();
  ImGui_ImplSdlGL3_Init(window_);
  ImGui::StyleColorsDark();
  set_style(ImGui::GetStyle());
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
    ImGui::Begin("Debug view");
    ImGui::Text("Time: %.2f", time);
    ImGui::Text("Framerate: %.1f fps", io.Framerate);
    ImGui::Text("Frametime: %.3f ms", 1000.0f / io.Framerate);
    ImGui::Checkbox("Autorotate", &options_->autorotate);
    ImGui::Checkbox("Wireframe", &options_->wireframe);
    ImGui::Checkbox("Strobe", &options_->strobe);
    ImGui::SliderFloat("Velocity", &options_->velocity, 0.0f, 5.0f);
    ImGui::SliderFloat("Sensitivity", &options_->sensitivity, 0.0f, 0.1f);

    if (ImGui::Button("Quit"))
      options_->quit = true;
    ImGui::End();
  }

  glViewport(0, 0, static_cast<int>(io.DisplaySize.x), static_cast<int>(io.DisplaySize.y));
  ImGui::Render();
  ImGui_ImplSdlGL3_RenderDrawData(ImGui::GetDrawData());
}

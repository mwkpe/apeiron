#include "gui.h"


#include "GL/glew.h"
#include "imgui/imgui.h"
#include "imgui/imgui_impl_sdl_gl3.h"


void apeiron::opengl::Gui::init()
{
  ImGui::CreateContext();
  ImGui_ImplSdlGL3_Init(window_);
  ImGui::StyleColorsDark();
}


void apeiron::opengl::Gui::process(SDL_Event* event)
{
  ImGui_ImplSdlGL3_ProcessEvent(event);
}


void apeiron::opengl::Gui::create_frame()
{
  ImGui_ImplSdlGL3_NewFrame(window_);
}


void apeiron::opengl::Gui::render()
{
  auto& io = ImGui::GetIO();
  glViewport(0, 0, static_cast<int>(io.DisplaySize.x), static_cast<int>(io.DisplaySize.y));
  ImGui::Render();
  ImGui_ImplSdlGL3_RenderDrawData(ImGui::GetDrawData());
}

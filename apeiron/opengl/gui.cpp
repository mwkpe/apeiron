#include "gui.h"


#include <string>
#include "imgui/imgui.h"
#include "imgui/imgui_impl_opengl3.h"
#include "imgui/imgui_impl_sdl3.h"


void apeiron::opengl::Gui::init(std::string_view glsl_version)
{
  ImGui::CreateContext();
  ImGui_ImplSDL3_InitForOpenGL(window_, context_);
  ImGui_ImplOpenGL3_Init(std::string{glsl_version}.c_str());
  ImGui::StyleColorsDark();
}


void apeiron::opengl::Gui::process(SDL_Event* event)
{
  ImGui_ImplSDL3_ProcessEvent(event);
}


void apeiron::opengl::Gui::create_frame()
{
  ImGui_ImplOpenGL3_NewFrame();
  ImGui_ImplSDL3_NewFrame();
  ImGui::NewFrame();
}


void apeiron::opengl::Gui::render() const
{
  ImGui::Render();
  ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

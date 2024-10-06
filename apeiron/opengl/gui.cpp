#include "gui.h"


#include <string>
#include <glad/glad.h>
#include "imgui/imgui.h"
#include "imgui/imgui_impl_opengl3.h"
#include "imgui/imgui_impl_sdl2.h"


void apeiron::opengl::Gui::init(std::string_view glsl_version)
{
  ImGui::CreateContext();
  ImGui_ImplSDL2_InitForOpenGL(window_, context_);
  ImGui_ImplOpenGL3_Init(std::string{glsl_version}.c_str());
  ImGui::StyleColorsDark();
}


void apeiron::opengl::Gui::process(SDL_Event* event)
{
  ImGui_ImplSDL2_ProcessEvent(event);
}


void apeiron::opengl::Gui::create_frame()
{
  ImGui_ImplOpenGL3_NewFrame();
  ImGui_ImplSDL2_NewFrame();
  ImGui::NewFrame();
}


void apeiron::opengl::Gui::render() const
{
  auto& io = ImGui::GetIO();
  ImGui::Render();
  glViewport(0, 0, static_cast<GLint>(io.DisplaySize.x), static_cast<GLint>(io.DisplaySize.y));
  ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

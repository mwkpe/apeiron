#include "gui.h"


#include "GL/glew.h"
#include "imgui/imgui.h"
#include "imgui/imgui_impl_opengl3.h"
#include "imgui/imgui_impl_sdl.h"


void apeiron::opengl::Gui::init()
{
  ImGui::CreateContext();
  ImGui_ImplSDL2_InitForOpenGL(window_, context_);
  ImGui_ImplOpenGL3_Init(nullptr);
  ImGui::StyleColorsDark();
}


void apeiron::opengl::Gui::process(SDL_Event* event)
{
  ImGui_ImplSDL2_ProcessEvent(event);
}


void apeiron::opengl::Gui::create_frame()
{
  ImGui_ImplOpenGL3_NewFrame();
  ImGui_ImplSDL2_NewFrame(window_);
  ImGui::NewFrame();
}


void apeiron::opengl::Gui::render()
{
  auto& io = ImGui::GetIO();
  ImGui::Render();
  glViewport(0, 0, static_cast<int>(io.DisplaySize.x), static_cast<int>(io.DisplaySize.y));
  ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

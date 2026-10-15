#include "gui.h"


#include <format>
#include <string>

#include "imgui/imgui.h"
#include "imgui/imgui_impl_opengl3.h"
#include "imgui/imgui_impl_sdl3.h"

#include "apeiron/engine/error.h"


apeiron::opengl::Gui::Gui(Gui&& other) noexcept
{
  window_ = other.window_;
  other.window_ = nullptr;

  context_ = other.context_;
  other.context_ = nullptr;

  initialized_ = other.initialized_;
  other.initialized_ = false;
}


auto apeiron::opengl::Gui::operator=(Gui&& other) noexcept -> Gui&
{
  if (&other == this) {
    return *this;
  }

  shutdown();

  window_ = other.window_;
  other.window_ = nullptr;

  context_ = other.context_;
  other.context_ = nullptr;

  initialized_ = other.initialized_;
  other.initialized_ = false;

  return *this;
}


apeiron::opengl::Gui::~Gui()
{
  shutdown();
}


void apeiron::opengl::Gui::init(int gl_major, int gl_minor)
{
  shutdown();

  ImGui::CreateContext();

  if (!ImGui_ImplSDL3_InitForOpenGL(window_, context_)) {
    ImGui::DestroyContext();
    throw engine::Error{"Error initializing ImGui SDL3 backend"};
  }

  if (!ImGui_ImplOpenGL3_Init(std::format("#version {}{}0", gl_major, gl_minor).c_str())) {
    ImGui_ImplSDL3_Shutdown();
    ImGui::DestroyContext();
    throw engine::Error{"Error initializing ImGui OpenGL3 backend"};
  }

  initialized_ = true;

  ImGui::StyleColorsDark();
  ImGui::GetIO().Fonts->AddFontDefaultVector();
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


void apeiron::opengl::Gui::shutdown()
{
  if (initialized_) {
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplSDL3_Shutdown();
    ImGui::DestroyContext();
    initialized_ = false;
  }
}

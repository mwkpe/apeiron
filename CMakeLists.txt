cmake_minimum_required(VERSION 3.9)
project(apeiron)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-O3 -Wall")

include_directories(C:/github/apeiron
    C:/libraries
    C:/libraries/SDL2/x86_64-w64-mingw32/include
    C:/libraries/glew/include
    C:/libraries/glm)
link_directories(C:/libraries/SDL2/x86_64-w64-mingw32/lib
    C:/libraries/glew/lib/Release/x64)

add_executable(apeiron
  opengl/shader.cpp opengl/shader.h
  opengl/renderer.cpp opengl/renderer.h
  opengl/shape.h
  opengl/cube.cpp opengl/cube.h
  opengl/cylinder.cpp opengl/cylinder.h
  opengl/model.cpp opengl/model.h
  opengl/gui.cpp opengl/gui.h
  engine/error.h
  engine/input.h
  engine/color.h
  engine/entity.h
  engine/camera.cpp engine/camera.h
  engine/model_loader.cpp engine/model_loader.h
  example/main.cpp
  example/options.h
  example/menu.h example/menu.cpp
  example/world.cpp example/world.h
  example/vehicle.cpp example/vehicle.h
  imgui/imgui.cpp imgui/imgui.h imgui/imgui_draw.cpp imgui/imgui_internal.h
  imgui/examples/sdl_opengl3_example/imgui_impl_sdl_gl3.cpp
  imgui/examples/sdl_opengl3_example/imgui_impl_sdl_gl3.h)
target_link_libraries(apeiron -lmingw32 -lglew32 -lglu32 -lopengl32 -lSDL2main -lSDL2)

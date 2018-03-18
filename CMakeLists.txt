cmake_minimum_required(VERSION 3.9)
project(apeiron)

set(CMAKE_CXX_STANDARD 17)

include_directories(C:/libraries/SDL2/x86_64-w64-mingw32/include
    C:/libraries/glew/include
    C:/libraries/glm)
link_directories(C:/libraries/SDL2/x86_64-w64-mingw32/lib
    C:/libraries/glew/lib/Release/x64)

add_executable(apeiron main.cpp world.cpp world.h shader.cpp shader.h error.h  gui.cpp gui.h
  imgui/imgui.cpp imgui/imgui.h imgui/imgui_draw.cpp imgui/imgui_internal.h
  imgui/examples/sdl_opengl3_example/imgui_impl_sdl_gl3.cpp
  imgui/examples/sdl_opengl3_example/imgui_impl_sdl_gl3.h primitives.h primitives.cpp options.h)

target_link_libraries(apeiron -lmingw32 -lglew32 -lglu32 -lopengl32 -lSDL2main -lSDL2)

cmake_minimum_required(VERSION 3.11)

add_library(apeiron-gui-sdl2-opengl3
    ${CMAKE_CURRENT_LIST_DIR}/../external/imgui/imgui.cpp
    ${CMAKE_CURRENT_LIST_DIR}/../external/imgui/imgui.h
    ${CMAKE_CURRENT_LIST_DIR}/../external/imgui/imgui_demo.cpp
    ${CMAKE_CURRENT_LIST_DIR}/../external/imgui/imgui_widgets.cpp
    ${CMAKE_CURRENT_LIST_DIR}/../external/imgui/imgui_tables.cpp
    ${CMAKE_CURRENT_LIST_DIR}/../external/imgui/imgui_draw.cpp
    ${CMAKE_CURRENT_LIST_DIR}/../external/imgui/imgui_internal.h
    ${CMAKE_CURRENT_LIST_DIR}/../external/imgui/imgui_impl_opengl3.cpp
    ${CMAKE_CURRENT_LIST_DIR}/../external/imgui/imgui_impl_opengl3.h
    ${CMAKE_CURRENT_LIST_DIR}/../external/imgui/imgui_impl_sdl.cpp
    ${CMAKE_CURRENT_LIST_DIR}/../external/imgui/imgui_impl_sdl.h
    ${CMAKE_CURRENT_LIST_DIR}/../opengl/gui.cpp
    ${CMAKE_CURRENT_LIST_DIR}/../opengl/gui.h)

if (WIN32)
  include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../external/SDL2/x86_64-w64-mingw32/include)
  link_directories(${CMAKE_CURRENT_SOURCE_DIR}/../external/SDL2/x86_64-w64-mingw32/lib)
endif ()

if (WIN32)
  target_link_libraries(apeiron-gui-sdl2-opengl3 -limm32 -lmingw32 -lglew32 -lglu32 -lopengl32 -lSDL2main -lSDL2)
elseif (UNIX AND NOT APPLE)
  target_link_libraries(apeiron-gui-sdl2-opengl3 -lGLEW -lGLU -lGL -lSDL2main -lSDL2)
endif ()

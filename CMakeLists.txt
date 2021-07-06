cmake_minimum_required(VERSION 3.11)

project(apeiron_example CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "-O3 -Wall -Wextra")

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

include(apeiron)
include(apeiron-gui-sdl2-opengl3)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/example)

if (WIN32)
  include_directories(${CMAKE_CURRENT_SOURCE_DIR}/external/SDL2/x86_64-w64-mingw32/include)
  link_directories(${CMAKE_CURRENT_SOURCE_DIR}/external/SDL2/x86_64-w64-mingw32/lib)
endif ()

add_executable(apeiron_example
    example/main.cpp
    example/settings.cpp
    example/settings.h
    example/menu.cpp
    example/menu.h
    example/cube.h
    example/cylinder.h
    example/ground_highlight.h
    example/world.cpp
    example/world.h)

if (WIN32 AND MINGW)
  target_link_libraries(apeiron_example apeiron apeiron-gui-sdl2-opengl3 -lmingw32 -lSDL2main -lSDL2)
elseif (UNIX AND NOT APPLE)
  target_link_libraries(apeiron_example apeiron apeiron-gui-sdl2-opengl3 -lSDL2main -lSDL2)
endif ()

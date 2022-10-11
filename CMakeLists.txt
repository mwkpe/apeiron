cmake_minimum_required(VERSION 3.11)

project(apeiron_example C CXX)  # Must specify C for glad library included by apeiron

set(CMAKE_CXX_STANDARD 20)
if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    set(CMAKE_CXX_FLAGS "-O3 -Wall -Wextra")
endif ()

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
set(SDL2_DIR "external/SDL2")

include(apeiron)
include(apeiron-gui-sdl2-opengl3)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/example)

if (WIN32 AND CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    include_directories(${SDL2_DIR}/x86_64-w64-mingw32/include)
    link_directories(${SDL2_DIR}/x86_64-w64-mingw32/lib)
elseif (WIN32 AND CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    include_directories(${SDL2_DIR}/include)
    link_directories(${SDL2_DIR}/lib)
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

if (WIN32 AND CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    target_link_libraries(apeiron_example apeiron apeiron-gui-sdl2-opengl3 -lmingw32 -lSDL2main -lSDL2)
elseif (WIN32 AND CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    target_link_libraries(apeiron_example apeiron apeiron-gui-sdl2-opengl3 SDL2main SDL2)
elseif (UNIX AND NOT APPLE)
    target_link_libraries(apeiron_example apeiron apeiron-gui-sdl2-opengl3 -lSDL2main -lSDL2)
endif ()

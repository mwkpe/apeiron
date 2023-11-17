cmake_minimum_required(VERSION 3.11)

project(apeiron_example C CXX)  # Must specify C for glad library included by apeiron

set(CMAKE_CXX_STANDARD 20)
if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    set(CMAKE_CXX_FLAGS "-O3 -Wall -Wextra")
endif ()

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

include(apeiron)
include(apeiron-gui-sdl2-opengl3)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/example)

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

target_link_libraries(apeiron_example apeiron apeiron-gui-sdl2-opengl3)

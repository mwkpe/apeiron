cmake_minimum_required(VERSION 3.20)

project(apeiron_example C CXX)  # Must specify C for glad library

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror=return-type")
  set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3")
  set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -O0")
endif ()

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake")

include(apeiron)
include(apeiron-gui-sdl3-opengl3)

add_executable(apeiron_example
    example/main.cpp
    example/settings.cpp
    example/settings.h
    example/menu.cpp
    example/menu.h
    example/cube.h
    example/ground_highlight.h
    example/world.cpp
    example/world.h)

target_include_directories(apeiron_example PRIVATE ${CMAKE_CURRENT_LIST_DIR}/external/private)
target_link_libraries(apeiron_example PRIVATE apeiron apeiron-gui-sdl3-opengl3)

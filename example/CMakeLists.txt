cmake_minimum_required(VERSION 3.20)

project(apeiron_example C CXX)  # Must specify C for glad library

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror=return-type")
  set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3")
  set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -O0")
endif ()

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/../cmake")

include(apeiron)
include(apeiron-gui-sdl3-opengl3)

add_executable(apeiron_example
    main.cpp
    settings.cpp
    settings.h
    menu.cpp
    menu.h
    cube.h
    ground_highlight.h
    world.cpp
    world.h)

target_include_directories(apeiron_example PRIVATE ${CMAKE_CURRENT_LIST_DIR}/../external/private)
target_link_libraries(apeiron_example PRIVATE apeiron apeiron-gui-sdl3-opengl3)

add_custom_command(TARGET apeiron_example POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    "${CMAKE_CURRENT_LIST_DIR}/../apeiron/opengl/shader"
    "$<TARGET_FILE_DIR:apeiron_example>/shader"
    VERBATIM)

add_custom_command(TARGET apeiron_example POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    "${CMAKE_CURRENT_LIST_DIR}/../assets"
    "$<TARGET_FILE_DIR:apeiron_example>/assets"
    VERBATIM)

if (WIN32)
  add_custom_command(TARGET apeiron_example POST_BUILD
      COMMAND ${CMAKE_COMMAND} -E copy_if_different
      "$<TARGET_FILE:SDL3::SDL3>"
      "$<TARGET_FILE_DIR:apeiron_example>"
      VERBATIM)
endif ()

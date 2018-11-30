cmake_minimum_required(VERSION 3.11)
project(apeiron_example)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-O3 -Wall -Wextra")

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/../cmake")

include(apeiron)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

if (WIN32)
  include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../external/SDL2/x86_64-w64-mingw32/include)
  link_directories(${CMAKE_CURRENT_SOURCE_DIR}/../external/SDL2/x86_64-w64-mingw32/lib)
endif ()

add_executable(apeiron_example
    main.cpp
    options.cpp
    options.h
    menu.cpp
    menu.h
    cube.h
    cylinder.h
    ground_highlight.h
    world.cpp
    world.h)

if (WIN32 AND MINGW)
  target_link_libraries(apeiron_example apeiron -lmingw32 -lSDL2main -lSDL2)
elseif (UNIX AND NOT APPLE)
  target_link_libraries(apeiron_example apeiron -lSDL2main -lSDL2)
endif ()

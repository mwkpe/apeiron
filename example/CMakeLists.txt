cmake_minimum_required(VERSION 3.11)
project(apeiron_example)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-O3 -Wall -Wextra")

include(../CMakeLists.txt)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/../external/SDL2/x86_64-w64-mingw32/include)

link_directories(${CMAKE_CURRENT_SOURCE_DIR}/../external/SDL2/x86_64-w64-mingw32/lib)

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

target_link_libraries(apeiron_example apeiron -lmingw32 -lopengl32 -lSDL2main -lSDL2)

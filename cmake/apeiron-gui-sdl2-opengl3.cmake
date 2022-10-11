set(SDL2_DIR "${CMAKE_CURRENT_LIST_DIR}/../external/SDL2")

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

if (WIN32 AND CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    include_directories(${SDL2_DIR}/x86_64-w64-mingw32/include)
    link_directories(${SDL2_DIR}/x86_64-w64-mingw32/lib)
elseif (WIN32 AND CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    include_directories(${SDL2_DIR}/include)
    link_directories(${SDL2_DIR}/lib)
endif ()

if (WIN32 AND CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    target_link_libraries(apeiron-gui-sdl2-opengl3 glad -limm32 -lmingw32 -lSDL2main -lSDL2)
elseif (WIN32 AND CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    target_link_libraries(apeiron-gui-sdl2-opengl3 glad imm32 SDL2main SDL2)
elseif (UNIX AND NOT APPLE)
  target_link_libraries(apeiron-gui-sdl2-opengl3 glad -lSDL2main -lSDL2)
endif ()

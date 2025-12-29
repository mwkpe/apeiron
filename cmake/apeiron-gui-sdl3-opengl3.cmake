add_library(apeiron-gui-sdl3-opengl3
    ${CMAKE_CURRENT_LIST_DIR}/../external/public/imgui/imconfig.h
    ${CMAKE_CURRENT_LIST_DIR}/../external/public/imgui/imgui.cpp
    ${CMAKE_CURRENT_LIST_DIR}/../external/public/imgui/imgui.h
    ${CMAKE_CURRENT_LIST_DIR}/../external/public/imgui/imgui_demo.cpp
    ${CMAKE_CURRENT_LIST_DIR}/../external/public/imgui/imgui_draw.cpp
    ${CMAKE_CURRENT_LIST_DIR}/../external/public/imgui/imgui_impl_opengl3.cpp
    ${CMAKE_CURRENT_LIST_DIR}/../external/public/imgui/imgui_impl_opengl3.h
    ${CMAKE_CURRENT_LIST_DIR}/../external/public/imgui/imgui_impl_opengl3_loader.h
    ${CMAKE_CURRENT_LIST_DIR}/../external/public/imgui/imgui_impl_sdl3.cpp
    ${CMAKE_CURRENT_LIST_DIR}/../external/public/imgui/imgui_impl_sdl3.h
    ${CMAKE_CURRENT_LIST_DIR}/../external/public/imgui/imgui_internal.h
    ${CMAKE_CURRENT_LIST_DIR}/../external/public/imgui/imgui_tables.cpp
    ${CMAKE_CURRENT_LIST_DIR}/../external/public/imgui/imgui_widgets.cpp
    ${CMAKE_CURRENT_LIST_DIR}/../external/public/imgui/imstb_rectpack.h
    ${CMAKE_CURRENT_LIST_DIR}/../external/public/imgui/imstb_textedit.h
    ${CMAKE_CURRENT_LIST_DIR}/../external/public/imgui/imstb_truetype.h 
    ${CMAKE_CURRENT_LIST_DIR}/../apeiron/opengl/gui.cpp
    ${CMAKE_CURRENT_LIST_DIR}/../apeiron/opengl/gui.h)

find_package(SDL3 CONFIG QUIET)

if (NOT TARGET SDL3::SDL3)
  # Fallback for Windows and MinGW
  if (WIN32 AND CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    set(_SDL3_ROOT "${CMAKE_CURRENT_LIST_DIR}/../external/public/SDL3/x86_64-w64-mingw32")

    add_library(SDL3::SDL3 UNKNOWN IMPORTED)
    set_target_properties(SDL3::SDL3 PROPERTIES
        IMPORTED_LOCATION "${_SDL3_ROOT}/lib/libSDL3.dll.a"
        INTERFACE_INCLUDE_DIRECTORIES "${_SDL3_ROOT}/include")
  else ()
    message(FATAL_ERROR "SDL3 not found")
  endif ()
endif ()

target_include_directories(apeiron-gui-sdl3-opengl3 PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/../external/public/imgui
    ${CMAKE_CURRENT_LIST_DIR}/../external/public)

target_link_libraries(apeiron-gui-sdl3-opengl3 PUBLIC glad SDL3::SDL3)

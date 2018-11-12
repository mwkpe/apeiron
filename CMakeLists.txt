cmake_minimum_required(VERSION 3.11)
project(apeiron CXX)

add_library(apeiron
    ${CMAKE_CURRENT_LIST_DIR}/external/imgui/imgui.cpp
    ${CMAKE_CURRENT_LIST_DIR}/external/imgui/imgui.h
    ${CMAKE_CURRENT_LIST_DIR}/external/imgui/imgui_widgets.cpp
    ${CMAKE_CURRENT_LIST_DIR}/external/imgui/imgui_draw.cpp
    ${CMAKE_CURRENT_LIST_DIR}/external/imgui/imgui_internal.h
    ${CMAKE_CURRENT_LIST_DIR}/external/imgui/imgui_impl_opengl3.cpp
    ${CMAKE_CURRENT_LIST_DIR}/external/imgui/imgui_impl_opengl3.h
    ${CMAKE_CURRENT_LIST_DIR}/external/imgui/imgui_impl_sdl.cpp
    ${CMAKE_CURRENT_LIST_DIR}/external/imgui/imgui_impl_sdl.h
    ${CMAKE_CURRENT_LIST_DIR}/utility/linear_range.h
    ${CMAKE_CURRENT_LIST_DIR}/engine/error.h
    ${CMAKE_CURRENT_LIST_DIR}/engine/vertex.h
    ${CMAKE_CURRENT_LIST_DIR}/engine/primitive.cpp
    ${CMAKE_CURRENT_LIST_DIR}/engine/primitive.h
    ${CMAKE_CURRENT_LIST_DIR}/engine/entity.h
    ${CMAKE_CURRENT_LIST_DIR}/engine/collision.cpp
    ${CMAKE_CURRENT_LIST_DIR}/engine/collision.h
    ${CMAKE_CURRENT_LIST_DIR}/engine/camera.cpp
    ${CMAKE_CURRENT_LIST_DIR}/engine/camera.h
    ${CMAKE_CURRENT_LIST_DIR}/engine/text.h
    ${CMAKE_CURRENT_LIST_DIR}/engine/input.h
    ${CMAKE_CURRENT_LIST_DIR}/engine/event.h
    ${CMAKE_CURRENT_LIST_DIR}/engine/image_loader.cpp
    ${CMAKE_CURRENT_LIST_DIR}/engine/image_loader.h
    ${CMAKE_CURRENT_LIST_DIR}/engine/model_loader.cpp
    ${CMAKE_CURRENT_LIST_DIR}/engine/model_loader.h
    ${CMAKE_CURRENT_LIST_DIR}/opengl/renderer.cpp
    ${CMAKE_CURRENT_LIST_DIR}/opengl/renderer.h
    ${CMAKE_CURRENT_LIST_DIR}/opengl/shader.cpp
    ${CMAKE_CURRENT_LIST_DIR}/opengl/shader.h
    ${CMAKE_CURRENT_LIST_DIR}/opengl/texture.cpp
    ${CMAKE_CURRENT_LIST_DIR}/opengl/texture.h
    ${CMAKE_CURRENT_LIST_DIR}/opengl/shape.cpp
    ${CMAKE_CURRENT_LIST_DIR}/opengl/shape.h
    ${CMAKE_CURRENT_LIST_DIR}/opengl/points.cpp
    ${CMAKE_CURRENT_LIST_DIR}/opengl/points.h
    ${CMAKE_CURRENT_LIST_DIR}/opengl/grid.cpp
    ${CMAKE_CURRENT_LIST_DIR}/opengl/grid.h
    ${CMAKE_CURRENT_LIST_DIR}/opengl/triangles.cpp
    ${CMAKE_CURRENT_LIST_DIR}/opengl/triangles.h
    ${CMAKE_CURRENT_LIST_DIR}/opengl/quad.cpp
    ${CMAKE_CURRENT_LIST_DIR}/opengl/quad.h
    ${CMAKE_CURRENT_LIST_DIR}/opengl/tileset.cpp
    ${CMAKE_CURRENT_LIST_DIR}/opengl/tileset.h
    ${CMAKE_CURRENT_LIST_DIR}/opengl/cuboid.cpp
    ${CMAKE_CURRENT_LIST_DIR}/opengl/cuboid.h
    ${CMAKE_CURRENT_LIST_DIR}/opengl/wire_cuboid.cpp
    ${CMAKE_CURRENT_LIST_DIR}/opengl/wire_cuboid.h
    ${CMAKE_CURRENT_LIST_DIR}/opengl/cylinder.cpp
    ${CMAKE_CURRENT_LIST_DIR}/opengl/cylinder.h
    ${CMAKE_CURRENT_LIST_DIR}/opengl/model.cpp
    ${CMAKE_CURRENT_LIST_DIR}/opengl/model.h
    ${CMAKE_CURRENT_LIST_DIR}/opengl/gui.cpp
    ${CMAKE_CURRENT_LIST_DIR}/opengl/gui.h
    ${CMAKE_CURRENT_LIST_DIR}/prefab/axis.h
    ${CMAKE_CURRENT_LIST_DIR}/prefab/axes.cpp
    ${CMAKE_CURRENT_LIST_DIR}/prefab/axes.h
    ${CMAKE_CURRENT_LIST_DIR}/prefab/ground.h
    ${CMAKE_CURRENT_LIST_DIR}/prefab/light.h
    ${CMAKE_CURRENT_LIST_DIR}/prefab/teapot.h)

list(APPEND APEIRON_INCLUDE_DIRECTORIES
    ${CMAKE_CURRENT_LIST_DIR}
    ${CMAKE_CURRENT_LIST_DIR}/external
    ${CMAKE_CURRENT_LIST_DIR}/external/glm)

if (WIN32)
  list(APPEND APEIRON_INCLUDE_DIRECTORIES ${CMAKE_CURRENT_LIST_DIR}/external/glew/include)
  link_directories(${CMAKE_CURRENT_LIST_DIR}/external/glew/lib/Release/x64)
endif ()

include_directories(${APEIRON_INCLUDE_DIRECTORIES})

if (WIN32)
  target_link_libraries(apeiron -lglew32 -lglu32 -lopengl32)
elseif (UNIX AND NOT APPLE)
  target_link_libraries(apeiron -lGLEW -lGLU -lGL)
endif ()

add_library(glad STATIC ${CMAKE_CURRENT_LIST_DIR}/../external/public/glad/source/glad.c)
target_include_directories(glad PUBLIC ${CMAKE_CURRENT_LIST_DIR}/../external/public/glad/include)

add_library(apeiron STATIC
    ${CMAKE_CURRENT_LIST_DIR}/../apeiron/engine/camera.cpp
    ${CMAKE_CURRENT_LIST_DIR}/../apeiron/engine/camera.h
    ${CMAKE_CURRENT_LIST_DIR}/../apeiron/engine/collision.cpp
    ${CMAKE_CURRENT_LIST_DIR}/../apeiron/engine/collision.h
    ${CMAKE_CURRENT_LIST_DIR}/../apeiron/engine/color_converter.h
    ${CMAKE_CURRENT_LIST_DIR}/../apeiron/engine/entity.h
    ${CMAKE_CURRENT_LIST_DIR}/../apeiron/engine/error.h
    ${CMAKE_CURRENT_LIST_DIR}/../apeiron/engine/event.h
    ${CMAKE_CURRENT_LIST_DIR}/../apeiron/engine/font.cpp
    ${CMAKE_CURRENT_LIST_DIR}/../apeiron/engine/font.h
    ${CMAKE_CURRENT_LIST_DIR}/../apeiron/engine/input.h
    ${CMAKE_CURRENT_LIST_DIR}/../apeiron/engine/image_loader.cpp
    ${CMAKE_CURRENT_LIST_DIR}/../apeiron/engine/image_loader.h
    ${CMAKE_CURRENT_LIST_DIR}/../apeiron/engine/model_loader.cpp
    ${CMAKE_CURRENT_LIST_DIR}/../apeiron/engine/model_loader.h
    ${CMAKE_CURRENT_LIST_DIR}/../apeiron/engine/primitive.cpp
    ${CMAKE_CURRENT_LIST_DIR}/../apeiron/engine/primitive.h
    ${CMAKE_CURRENT_LIST_DIR}/../apeiron/engine/sdl_input.h
    ${CMAKE_CURRENT_LIST_DIR}/../apeiron/engine/sdl_window_wrapper.cpp
    ${CMAKE_CURRENT_LIST_DIR}/../apeiron/engine/sdl_window_wrapper.h
    ${CMAKE_CURRENT_LIST_DIR}/../apeiron/engine/transform.cpp
    ${CMAKE_CURRENT_LIST_DIR}/../apeiron/engine/transform.h
    ${CMAKE_CURRENT_LIST_DIR}/../apeiron/engine/vertex.h
    ${CMAKE_CURRENT_LIST_DIR}/../apeiron/opengl/command_buffer.cpp
    ${CMAKE_CURRENT_LIST_DIR}/../apeiron/opengl/command_buffer.h
    ${CMAKE_CURRENT_LIST_DIR}/../apeiron/opengl/cuboid.cpp
    ${CMAKE_CURRENT_LIST_DIR}/../apeiron/opengl/cuboid.h
    ${CMAKE_CURRENT_LIST_DIR}/../apeiron/opengl/cylinder.cpp
    ${CMAKE_CURRENT_LIST_DIR}/../apeiron/opengl/cylinder.h
    ${CMAKE_CURRENT_LIST_DIR}/../apeiron/opengl/frame_buffer.cpp
    ${CMAKE_CURRENT_LIST_DIR}/../apeiron/opengl/frame_buffer.h
    ${CMAKE_CURRENT_LIST_DIR}/../apeiron/opengl/grid.cpp
    ${CMAKE_CURRENT_LIST_DIR}/../apeiron/opengl/grid.h
    ${CMAKE_CURRENT_LIST_DIR}/../apeiron/opengl/meshset.cpp
    ${CMAKE_CURRENT_LIST_DIR}/../apeiron/opengl/meshset.h
    ${CMAKE_CURRENT_LIST_DIR}/../apeiron/opengl/model.cpp
    ${CMAKE_CURRENT_LIST_DIR}/../apeiron/opengl/model.h
    ${CMAKE_CURRENT_LIST_DIR}/../apeiron/opengl/points.cpp
    ${CMAKE_CURRENT_LIST_DIR}/../apeiron/opengl/points.h
    ${CMAKE_CURRENT_LIST_DIR}/../apeiron/opengl/quad.cpp
    ${CMAKE_CURRENT_LIST_DIR}/../apeiron/opengl/quad.h
    ${CMAKE_CURRENT_LIST_DIR}/../apeiron/opengl/renderer.cpp
    ${CMAKE_CURRENT_LIST_DIR}/../apeiron/opengl/renderer.h
    ${CMAKE_CURRENT_LIST_DIR}/../apeiron/opengl/shader.cpp
    ${CMAKE_CURRENT_LIST_DIR}/../apeiron/opengl/shader.h
    ${CMAKE_CURRENT_LIST_DIR}/../apeiron/opengl/shader_storage_buffer.cpp
    ${CMAKE_CURRENT_LIST_DIR}/../apeiron/opengl/shader_storage_buffer.h
    ${CMAKE_CURRENT_LIST_DIR}/../apeiron/opengl/texture.cpp
    ${CMAKE_CURRENT_LIST_DIR}/../apeiron/opengl/texture.h
    ${CMAKE_CURRENT_LIST_DIR}/../apeiron/opengl/tileset.cpp
    ${CMAKE_CURRENT_LIST_DIR}/../apeiron/opengl/tileset.h
    ${CMAKE_CURRENT_LIST_DIR}/../apeiron/opengl/triangles.cpp
    ${CMAKE_CURRENT_LIST_DIR}/../apeiron/opengl/triangles.h
    ${CMAKE_CURRENT_LIST_DIR}/../apeiron/opengl/vertex_array.cpp
    ${CMAKE_CURRENT_LIST_DIR}/../apeiron/opengl/vertex_array.h
    ${CMAKE_CURRENT_LIST_DIR}/../apeiron/prefab/axis.h
    ${CMAKE_CURRENT_LIST_DIR}/../apeiron/prefab/axes.cpp
    ${CMAKE_CURRENT_LIST_DIR}/../apeiron/prefab/axes.h
    ${CMAKE_CURRENT_LIST_DIR}/../apeiron/prefab/grid.cpp
    ${CMAKE_CURRENT_LIST_DIR}/../apeiron/prefab/grid.h
    ${CMAKE_CURRENT_LIST_DIR}/../apeiron/prefab/text.cpp
    ${CMAKE_CURRENT_LIST_DIR}/../apeiron/prefab/text.h
    ${CMAKE_CURRENT_LIST_DIR}/../apeiron/prefab/light.h
    ${CMAKE_CURRENT_LIST_DIR}/../apeiron/prefab/teapot.h
    ${CMAKE_CURRENT_LIST_DIR}/../apeiron/utility/linear_range.h
    ${CMAKE_CURRENT_LIST_DIR}/../apeiron/utility/timer.cpp
    ${CMAKE_CURRENT_LIST_DIR}/../apeiron/utility/timer.h)

target_include_directories(apeiron PUBLIC ${CMAKE_CURRENT_LIST_DIR}/..
    PRIVATE ${CMAKE_CURRENT_LIST_DIR}/../external/private)

find_package(glm CONFIG QUIET)

if (NOT TARGET glm::glm)
  add_library(glm INTERFACE)
  add_library(glm::glm ALIAS glm)
  target_include_directories(glm INTERFACE ${CMAKE_CURRENT_LIST_DIR}/../external/public/glm)
endif ()

target_compile_definitions(apeiron PUBLIC GLM_ENABLE_EXPERIMENTAL)
target_link_libraries(apeiron PUBLIC glad glm::glm)

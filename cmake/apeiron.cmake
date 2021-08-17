add_library(glad ${CMAKE_CURRENT_LIST_DIR}/../external/glad/src/glad.c)

add_library(apeiron
    ${CMAKE_CURRENT_LIST_DIR}/../utility/linear_range.h
    ${CMAKE_CURRENT_LIST_DIR}/../utility/timer.cpp
    ${CMAKE_CURRENT_LIST_DIR}/../utility/timer.h
    ${CMAKE_CURRENT_LIST_DIR}/../engine/error.h
    ${CMAKE_CURRENT_LIST_DIR}/../engine/vertex.h
    ${CMAKE_CURRENT_LIST_DIR}/../engine/primitive.cpp
    ${CMAKE_CURRENT_LIST_DIR}/../engine/primitive.h
    ${CMAKE_CURRENT_LIST_DIR}/../engine/entity.h
    ${CMAKE_CURRENT_LIST_DIR}/../engine/collision.cpp
    ${CMAKE_CURRENT_LIST_DIR}/../engine/collision.h
    ${CMAKE_CURRENT_LIST_DIR}/../engine/camera.cpp
    ${CMAKE_CURRENT_LIST_DIR}/../engine/camera.h
    ${CMAKE_CURRENT_LIST_DIR}/../engine/text.h
    ${CMAKE_CURRENT_LIST_DIR}/../engine/input.h
    ${CMAKE_CURRENT_LIST_DIR}/../engine/event.h
    ${CMAKE_CURRENT_LIST_DIR}/../engine/image_loader.cpp
    ${CMAKE_CURRENT_LIST_DIR}/../engine/image_loader.h
    ${CMAKE_CURRENT_LIST_DIR}/../engine/model_loader.cpp
    ${CMAKE_CURRENT_LIST_DIR}/../engine/model_loader.h
    ${CMAKE_CURRENT_LIST_DIR}/../opengl/renderer.cpp
    ${CMAKE_CURRENT_LIST_DIR}/../opengl/renderer.h
    ${CMAKE_CURRENT_LIST_DIR}/../opengl/frame_buffer.cpp
    ${CMAKE_CURRENT_LIST_DIR}/../opengl/frame_buffer.h
    ${CMAKE_CURRENT_LIST_DIR}/../opengl/shader.cpp
    ${CMAKE_CURRENT_LIST_DIR}/../opengl/shader.h
    ${CMAKE_CURRENT_LIST_DIR}/../opengl/texture.cpp
    ${CMAKE_CURRENT_LIST_DIR}/../opengl/texture.h
    ${CMAKE_CURRENT_LIST_DIR}/../opengl/shape.cpp
    ${CMAKE_CURRENT_LIST_DIR}/../opengl/shape.h
    ${CMAKE_CURRENT_LIST_DIR}/../opengl/points.cpp
    ${CMAKE_CURRENT_LIST_DIR}/../opengl/points.h
    ${CMAKE_CURRENT_LIST_DIR}/../opengl/grid.cpp
    ${CMAKE_CURRENT_LIST_DIR}/../opengl/grid.h
    ${CMAKE_CURRENT_LIST_DIR}/../opengl/triangles.cpp
    ${CMAKE_CURRENT_LIST_DIR}/../opengl/triangles.h
    ${CMAKE_CURRENT_LIST_DIR}/../opengl/quad.cpp
    ${CMAKE_CURRENT_LIST_DIR}/../opengl/quad.h
    ${CMAKE_CURRENT_LIST_DIR}/../opengl/tileset.cpp
    ${CMAKE_CURRENT_LIST_DIR}/../opengl/tileset.h
    ${CMAKE_CURRENT_LIST_DIR}/../opengl/cuboid.cpp
    ${CMAKE_CURRENT_LIST_DIR}/../opengl/cuboid.h
    ${CMAKE_CURRENT_LIST_DIR}/../opengl/wire_cuboid.cpp
    ${CMAKE_CURRENT_LIST_DIR}/../opengl/wire_cuboid.h
    ${CMAKE_CURRENT_LIST_DIR}/../opengl/cylinder.cpp
    ${CMAKE_CURRENT_LIST_DIR}/../opengl/cylinder.h
    ${CMAKE_CURRENT_LIST_DIR}/../opengl/mesh_font.cpp
    ${CMAKE_CURRENT_LIST_DIR}/../opengl/mesh_font.h
    ${CMAKE_CURRENT_LIST_DIR}/../opengl/model.cpp
    ${CMAKE_CURRENT_LIST_DIR}/../opengl/model.h
    ${CMAKE_CURRENT_LIST_DIR}/../prefab/axis.h
    ${CMAKE_CURRENT_LIST_DIR}/../prefab/axes.cpp
    ${CMAKE_CURRENT_LIST_DIR}/../prefab/axes.h
    ${CMAKE_CURRENT_LIST_DIR}/../prefab/ground.h
    ${CMAKE_CURRENT_LIST_DIR}/../prefab/light.h
    ${CMAKE_CURRENT_LIST_DIR}/../prefab/teapot.h)

list(APPEND APEIRON_INCLUDE_DIRECTORIES
    ${CMAKE_CURRENT_LIST_DIR}/..
    ${CMAKE_CURRENT_LIST_DIR}/../external
    ${CMAKE_CURRENT_LIST_DIR}/../external/glm
    ${CMAKE_CURRENT_LIST_DIR}/../external/glad/include)

include_directories(${APEIRON_INCLUDE_DIRECTORIES})
target_link_libraries(apeiron glad)

#include "model_loader.h"


#define TINYOBJLOADER_IMPLEMENTATION
#include "tiny_obj_loader.h"
#include "apeiron/engine/error.h"
#include "apeiron/utility/timer.h"


namespace {


template<typename T> T get_vertex(const tinyobj::attrib_t& attrib, const tinyobj::index_t& index)
{
  float x = attrib.vertices[3 * index.vertex_index + 0];
  float y = attrib.vertices[3 * index.vertex_index + 1];
  float z = attrib.vertices[3 * index.vertex_index + 2];

  if constexpr (std::is_same<T, apeiron::engine::Vertex_simple>::value) {
    return {x, y, z};
  }

  [[maybe_unused]] float nx, ny, nz;
  if constexpr (std::is_same<T, apeiron::engine::Vertex>::value ||
      std::is_same<T, apeiron::engine::Vertex_normal>::value ||
      std::is_same<T, apeiron::engine::Vertex_normal_texcoords>::value ||
      std::is_same<T, apeiron::engine::Vertex_normal_color>::value) {
    if (attrib.normals.empty()) {
      nx = ny = nz = 0.0f;
    }
    else {
      nx = attrib.normals[3 * index.normal_index + 0];
      ny = attrib.normals[3 * index.normal_index + 1];
      nz = attrib.normals[3 * index.normal_index + 2];
    }
  }

  [[maybe_unused]] float s, t;
  if constexpr (std::is_same<T, apeiron::engine::Vertex>::value ||
      std::is_same<T, apeiron::engine::Vertex_texcoords>::value ||
      std::is_same<T, apeiron::engine::Vertex_normal_texcoords>::value) {
    if (attrib.texcoords.empty()) {
      s = t = 0.0f;
    }
    else {
      s = attrib.texcoords[2 * index.texcoord_index + 0];
      t = attrib.texcoords[2 * index.texcoord_index + 1];
    }
  }

  [[maybe_unused]] float r, g, b;
  if constexpr (std::is_same<T, apeiron::engine::Vertex>::value ||
      std::is_same<T, apeiron::engine::Vertex_color>::value ||
      std::is_same<T, apeiron::engine::Vertex_normal_color>::value) {
    // Color defaulted to white in LoadObj
    r = attrib.colors[3 * index.vertex_index + 0];
    g = attrib.colors[3 * index.vertex_index + 1];
    b = attrib.colors[3 * index.vertex_index + 2];
  }

  if constexpr (std::is_same<T, apeiron::engine::Vertex>::value) {
    return {{x, y, z}, {nx, ny, nz}, {s, t}, {r, g, b, 1.0f}};
  }
  else if constexpr (std::is_same<T, apeiron::engine::Vertex_normal>::value) {
    return {{x, y, z}, {nx, ny, nz}};
  }
  else if constexpr (std::is_same<T, apeiron::engine::Vertex_color>::value) {
    return {{x, y, z}, {r, g, b, 1.0f}};
  }
  else if constexpr (std::is_same<T, apeiron::engine::Vertex_texcoords>::value) {
    return {{x, y, z}, {s, t}};
  }
  else if constexpr (std::is_same<T, apeiron::engine::Vertex_normal_color>::value) {
    return {{x, y, z}, {nx, ny, nz}, {r, g, b, 1.0f}};
  }
  else if constexpr (std::is_same<T, apeiron::engine::Vertex_normal_texcoords>::value) {
    return {{x, y, z}, {nx, ny, nz}, {s, t}};
  }
}


}  // namespace


template<typename T> auto apeiron::engine::load_model(std::string_view filename) -> Model_data<T>
{
  utility::Scope_timer timer{std::string{filename}};

  tinyobj::attrib_t attrib;
  std::vector<tinyobj::shape_t> shapes;
  std::vector<tinyobj::material_t> materials;
  std::string error;
  std::string warning;

  if (!tinyobj::LoadObj(&attrib, &shapes, &materials, &warning, &error,
      std::string{filename}.c_str(), nullptr, true, true)) {
    throw engine::Error{error};
  }

  Model_data<T> model_data;

  for (const auto& material : materials) {
    Material_data material_data;
    material_data.diffuse_texture_filename = material.diffuse_texname;
    model_data.materials.push_back(std::move(material_data));
  }

  for (const auto& shape : shapes) {
    Mesh_data<T> mesh_data;
    std::size_t index_offset = 0;
    for (std::size_t f=0; f<shape.mesh.num_face_vertices.size(); ++f) {
      auto fv = shape.mesh.num_face_vertices[f];
      for (std::size_t v=0; v<fv; ++v) {
        tinyobj::index_t index = shape.mesh.indices[index_offset + v];
        mesh_data.vertices.push_back(get_vertex<T>(attrib, index));
      }
      index_offset += fv;
    }
    model_data.meshes.push_back(std::move(mesh_data));
  }

  return model_data;
}


template auto apeiron::engine::load_model(std::string_view filename) -> Model_data<apeiron::engine::Vertex>;
template auto apeiron::engine::load_model(std::string_view filename) -> Model_data<apeiron::engine::Vertex_simple>;
template auto apeiron::engine::load_model(std::string_view filename) -> Model_data<apeiron::engine::Vertex_normal>;
template auto apeiron::engine::load_model(std::string_view filename) -> Model_data<apeiron::engine::Vertex_color>;
template auto apeiron::engine::load_model(std::string_view filename) -> Model_data<apeiron::engine::Vertex_texcoords>;
template auto apeiron::engine::load_model(std::string_view filename) -> Model_data<apeiron::engine::Vertex_normal_color>;
template auto apeiron::engine::load_model(std::string_view filename) -> Model_data<apeiron::engine::Vertex_normal_texcoords>;

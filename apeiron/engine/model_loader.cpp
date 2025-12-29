#include "model_loader.h"


#include <type_traits>

#define TINYOBJLOADER_IMPLEMENTATION
#include "tiny_obj_loader.h"

#include "apeiron/engine/error.h"


namespace {


template<typename T> concept has_normal = requires(T v) {
  { v.normal } -> std::same_as<glm::vec3&>;
};

template<typename T> concept has_texcoords = requires(T v) {
  { v.texcoords } -> std::same_as<glm::vec2&>;
};

template<typename T> concept has_color = requires(T v) {
  { v.color } -> std::same_as<glm::vec4&>;
};


template<typename T> T get_vertex(const tinyobj::attrib_t& attrib, const tinyobj::index_t& index)
{
  float x = attrib.vertices[3 * index.vertex_index + 0];
  float y = attrib.vertices[3 * index.vertex_index + 1];
  float z = attrib.vertices[3 * index.vertex_index + 2];

  if constexpr (std::is_same<T, apeiron::engine::Vertex_simple>::value) {
    return {x, y, z};
  }

  [[maybe_unused]] float nx, ny, nz;
  if constexpr (has_normal<T>) {
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
  if constexpr (has_texcoords<T>) {
    if (attrib.texcoords.empty()) {
      s = t = 0.0f;
    }
    else {
      s = attrib.texcoords[2 * index.texcoord_index + 0];
      t = attrib.texcoords[2 * index.texcoord_index + 1];
    }
  }

  [[maybe_unused]] float r, g, b;
  if constexpr (has_color<T>) {
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


template<typename T> auto apeiron::engine::load_model(std::string_view filename) -> Model<T>
{
  tinyobj::attrib_t attrib;
  std::vector<tinyobj::shape_t> shapes;
  std::vector<tinyobj::material_t> materials;
  std::string error;
  std::string warning;

  if (!tinyobj::LoadObj(&attrib, &shapes, &materials, &warning, &error,
      std::string{filename}.c_str(), nullptr, true, true)) {
    throw engine::Error{error};
  }

  Model<T> model;

  for (const auto& material : materials) {
    model.materials.emplace_back(material.diffuse_texname);
  }

  for (const auto& shape : shapes) {
    Mesh<T> mesh;
    std::size_t index_offset = 0;

    for (std::size_t f=0; f<shape.mesh.num_face_vertices.size(); ++f) {
      auto fv = shape.mesh.num_face_vertices[f];

      for (std::size_t v=0; v<fv; ++v) {
        tinyobj::index_t index = shape.mesh.indices[index_offset + v];
        mesh.vertices.push_back(get_vertex<T>(attrib, index));
      }

      index_offset += fv;
    }
    model.meshes.push_back(std::move(mesh));
  }

  return model;
}


namespace apeiron::engine {


template auto load_model(std::string_view filename) -> Model<Vertex>;
template auto load_model(std::string_view filename) -> Model<Vertex_simple>;
template auto load_model(std::string_view filename) -> Model<Vertex_normal>;
template auto load_model(std::string_view filename) -> Model<Vertex_color>;
template auto load_model(std::string_view filename) -> Model<Vertex_texcoords>;
template auto load_model(std::string_view filename) -> Model<Vertex_normal_color>;
template auto load_model(std::string_view filename) -> Model<Vertex_normal_texcoords>;


}  // namespace apeiron::engine

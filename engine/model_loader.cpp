#include "model_loader.h"


#define TINYOBJLOADER_IMPLEMENTATION
#include "tiny_obj_loader.h"
#include "engine/error.h"


namespace {


template<typename T>
auto get(const tinyobj::attrib_t& attrib, const tinyobj::index_t& index)
{
  using namespace apeiron::engine;

  float x = attrib.vertices[3*index.vertex_index+0];
  float y = attrib.vertices[3*index.vertex_index+1];
  float z = attrib.vertices[3*index.vertex_index+2];

  // Normal
  [[maybe_unused]] float nx, ny, nz;
  if constexpr (std::is_same<T, Vertex>::value ||
      std::is_same<T, Vertex_normal>::value ||
      std::is_same<T, Vertex_normal_color>::value ||
      std::is_same<T, Vertex_normal_texcoords>::value) {   
    if (attrib.normals.empty()) {
      nx = ny = nz = 0.0f;
    }
    else {
      nx = attrib.normals[3*index.normal_index+0];
      ny = attrib.normals[3*index.normal_index+1];
      nz = attrib.normals[3*index.normal_index+2];
    }
  }

  // Texture coordinates
  [[maybe_unused]] float s, t;
  if constexpr (std::is_same<T, Vertex>::value ||
      std::is_same<T, Vertex_texcoords>::value ||
      std::is_same<T, Vertex_normal_texcoords>::value) {
    if (attrib.texcoords.empty()) {
      s = t = 0.0f;
    }
    else {
      s = attrib.texcoords[2*index.texcoord_index+0];
      t = attrib.texcoords[2*index.texcoord_index+1];
    }
  }

  // Color
  [[maybe_unused]] float r, g, b;
  if constexpr (std::is_same<T, Vertex>::value ||
      std::is_same<T, Vertex_color>::value ||
      std::is_same<T, Vertex_normal_color>::value) {
    if (attrib.colors.empty()) {
      r = g = b = 0.0f;
    }
    else {
      r = attrib.colors[3*index.vertex_index+0];
      g = attrib.colors[3*index.vertex_index+1];
      b = attrib.colors[3*index.vertex_index+2];
    }
  }

  if constexpr (std::is_same<T, Vertex>::value) {
    return T{x, y, z, nx, ny, nz, s, t, r, g, b};
  }
  else if constexpr (std::is_same<T, Vertex_simple>::value) {
    return T{x, y, z};
  }
  else if constexpr (std::is_same<T, Vertex_normal>::value) {
    return T{x, y, z, nx, ny, nz};
  }
  else if constexpr (std::is_same<T, Vertex_color>::value) {
    return T{x, y, z, r, g, b};
  }
  else if constexpr (std::is_same<T, Vertex_texcoords>::value) {
    return T{x, y, z, s, t};
  }
  else if constexpr (std::is_same<T, Vertex_normal_color>::value) {
    return T{x, y, z, nx, ny, nz, r, g, b};
  }
  else if constexpr (std::is_same<T, Vertex_normal_texcoords>::value) {
    return T{x, y, z, nx, ny, nz, s, t};
  }
}


}  // namespace


template<typename T = apeiron::engine::Vertex>
std::vector<T> apeiron::engine::load_model(std::string_view filename)
{
  tinyobj::attrib_t attrib;
  std::vector<tinyobj::shape_t> shapes;
  std::vector<tinyobj::material_t> materials;
  std::string error;

  if (!tinyobj::LoadObj(&attrib, &shapes, &materials, &error, std::string{filename}.c_str())) {
    throw engine::Error{error};
  }

  std::vector<T> vertices;
  for (const auto& shape : shapes) {
    std::size_t index_offset = 0;
    for (std::size_t f=0; f<shape.mesh.num_face_vertices.size(); ++f) {
      auto fv = shape.mesh.num_face_vertices[f];
      for (std::size_t v=0; v<fv; ++v) {
        tinyobj::index_t index = shape.mesh.indices[index_offset + v];
        vertices.push_back(get<T>(attrib, index));
      }
      index_offset += fv;
    }
  }

  return vertices;
}


using namespace apeiron::engine;
template std::vector<Vertex> load_model(std::string_view filename);
template std::vector<Vertex_simple> load_model(std::string_view filename);
template std::vector<Vertex_normal> load_model(std::string_view filename);
template std::vector<Vertex_color> load_model(std::string_view filename);
template std::vector<Vertex_texcoords> load_model(std::string_view filename);
template std::vector<Vertex_normal_color> load_model(std::string_view filename);
template std::vector<Vertex_normal_texcoords> load_model(std::string_view filename);

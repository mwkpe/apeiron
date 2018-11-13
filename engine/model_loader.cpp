#include "model_loader.h"


#define TINYOBJLOADER_IMPLEMENTATION
#include "tiny_obj_loader.h"
#include "engine/error.h"


namespace {



apeiron::engine::Vertex get_vertex(const tinyobj::attrib_t& attrib, const tinyobj::index_t& index)
{
  float x = attrib.vertices[3 * index.vertex_index + 0];
  float y = attrib.vertices[3 * index.vertex_index + 1];
  float z = attrib.vertices[3 * index.vertex_index + 2];

  float nx, ny, nz;
  if (attrib.normals.empty()) {
    nx = ny = nz = 0.0f;
  }
  else {
    nx = attrib.normals[3 * index.normal_index + 0];
    ny = attrib.normals[3 * index.normal_index + 1];
    nz = attrib.normals[3 * index.normal_index + 2];
  }

  float s, t;
  if (attrib.texcoords.empty()) {
    s = t = 0.0f;
  }
  else {
    s = attrib.texcoords[2 * index.texcoord_index + 0];
    t = attrib.texcoords[2 * index.texcoord_index + 1];
  }

  // Color defaulted to white in LoadObj
  float r = attrib.colors[3 * index.vertex_index + 0];
  float g = attrib.colors[3 * index.vertex_index + 1];
  float b = attrib.colors[3 * index.vertex_index + 2];

  return {{x, y, z}, {nx, ny, nz}, {s, t}, {r, g, b, 1.0f}};
}


}  // namespace


auto apeiron::engine::load_model(std::string_view filename) -> std::vector<std::vector<Vertex>>
{
  tinyobj::attrib_t attrib;
  std::vector<tinyobj::shape_t> shapes;
  std::vector<tinyobj::material_t> materials;
  std::string error;

  if (!tinyobj::LoadObj(&attrib, &shapes, &materials, &error, std::string{filename}.c_str(),
      nullptr, true, true)) {
    throw engine::Error{error};
  }

  std::vector<std::vector<Vertex>> meshes;
  for (const auto& shape : shapes) {
    meshes.emplace_back();
    auto& mesh = meshes.back();
    std::size_t index_offset = 0;
    for (std::size_t f=0; f<shape.mesh.num_face_vertices.size(); ++f) {
      auto fv = shape.mesh.num_face_vertices[f];
      for (std::size_t v=0; v<fv; ++v) {
        tinyobj::index_t index = shape.mesh.indices[index_offset + v];
        mesh.push_back(get_vertex(attrib, index));
      }
      index_offset += fv;
    }
  }

  return meshes;
}

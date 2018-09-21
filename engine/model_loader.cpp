#include "model_loader.h"


#define TINYOBJLOADER_IMPLEMENTATION
#include "tiny_obj_loader.h"
#include "engine/model_flags.h"
#include "engine/error.h"


std::tuple<std::vector<float>, int> apeiron::engine::load_model(std::string_view filename, std::uint32_t flags)
{
  tinyobj::attrib_t attrib;
  std::vector<tinyobj::shape_t> shapes;
  std::vector<tinyobj::material_t> materials;
  std::string error;
  if (!tinyobj::LoadObj(&attrib, &shapes, &materials, &error, std::string{filename}.c_str())) {
    throw engine::Error{error};
  }

  std::vector<float> vertices;
  for (const auto& shape : shapes) {
    std::size_t index_offset = 0;
    for (std::size_t f=0; f<shape.mesh.num_face_vertices.size(); ++f) {
      auto fv = shape.mesh.num_face_vertices[f];
      for (std::size_t v=0; v<fv; ++v) {
        tinyobj::index_t idx = shape.mesh.indices[index_offset + v];
        if (flags & model_flags::vertices) {
          vertices.push_back(attrib.vertices[3*idx.vertex_index+0]);
          vertices.push_back(attrib.vertices[3*idx.vertex_index+1]);
          vertices.push_back(attrib.vertices[3*idx.vertex_index+2]);
        }
        if (flags & model_flags::normals) {
          vertices.push_back(attrib.normals[3*idx.normal_index+0]);
          vertices.push_back(attrib.normals[3*idx.normal_index+1]);
          vertices.push_back(attrib.normals[3*idx.normal_index+2]);
        }
        if (flags & model_flags::texcoords) {
          vertices.push_back(attrib.texcoords[2*idx.texcoord_index+0]);
          vertices.push_back(attrib.texcoords[2*idx.texcoord_index+1]);
        }
        if (flags & model_flags::colors) {
          vertices.push_back(attrib.colors[3*idx.vertex_index+0]);
          vertices.push_back(attrib.colors[3*idx.vertex_index+1]);
          vertices.push_back(attrib.colors[3*idx.vertex_index+2]);
          vertices.push_back(1.0f);
        }
      }
      index_offset += fv;
    }
  }

  int elements_per_vertex = 0;
  if (flags & model_flags::vertices)
    elements_per_vertex += 3;
  if (flags & model_flags::normals)
    elements_per_vertex += 3;
  if (flags & model_flags::texcoords)
    elements_per_vertex += 2;
  if (flags & model_flags::colors)
    elements_per_vertex += 4;

  return {vertices, elements_per_vertex};
}

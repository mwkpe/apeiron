#include "model_loader.h"


#define TINYOBJLOADER_IMPLEMENTATION
#include "tiny_obj_loader.h"
#include "engine/model_flags.h"
#include "engine/error.h"


std::tuple<std::vector<float>, int> apeiron::engine::load_model(std::string_view filename, int flags)
{
  tinyobj::attrib_t attrib;
  std::vector<tinyobj::shape_t> shapes;
  std::vector<tinyobj::material_t> materials;
  std::string error;
  if (!tinyobj::LoadObj(&attrib, &shapes, &materials, &error, std::string{filename}.c_str())) {
    throw engine::Error{error};
  }

  std::vector<float> vertices;
  for (std::size_t s=0; s<shapes.size(); ++s) {
    std::size_t index_offset = 0;
    for (std::size_t f=0; f<shapes[s].mesh.num_face_vertices.size(); ++f) {
      auto fv = shapes[s].mesh.num_face_vertices[f];
      for (std::size_t v=0; v<fv; ++v) {
        tinyobj::index_t idx = shapes[s].mesh.indices[index_offset + v];
        if (flags & model_flags::vertices) {
          tinyobj::real_t x = attrib.vertices[3*idx.vertex_index+0];
          tinyobj::real_t y = attrib.vertices[3*idx.vertex_index+1];
          tinyobj::real_t z = attrib.vertices[3*idx.vertex_index+2];
          vertices.push_back(x);
          vertices.push_back(y);
          vertices.push_back(z);
        }
        if (flags & model_flags::normals) {
          tinyobj::real_t x = attrib.normals[3*idx.normal_index+0];
          tinyobj::real_t y = attrib.normals[3*idx.normal_index+1];
          tinyobj::real_t z = attrib.normals[3*idx.normal_index+2];
          vertices.push_back(x);
          vertices.push_back(y);
          vertices.push_back(z);
        }
        if (flags & model_flags::tex_coords) {
          tinyobj::real_t s = attrib.texcoords[2*idx.texcoord_index+0];
          tinyobj::real_t t = attrib.texcoords[2*idx.texcoord_index+1];
          vertices.push_back(s);
          vertices.push_back(t);
        }
        if (flags & model_flags::colors) {
          tinyobj::real_t r = attrib.colors[3*idx.vertex_index+0];
          tinyobj::real_t g = attrib.colors[3*idx.vertex_index+1];
          tinyobj::real_t b = attrib.colors[3*idx.vertex_index+2];
          vertices.push_back(r);
          vertices.push_back(g);
          vertices.push_back(b);
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
  if (flags & model_flags::tex_coords)
    elements_per_vertex += 2;
  if (flags & model_flags::colors)
    elements_per_vertex += 3;

  return {vertices, elements_per_vertex};
}

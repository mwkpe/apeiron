#include "model_loader.h"

#include <iostream>
#define TINYOBJLOADER_IMPLEMENTATION
#include "tiny_obj_loader.h"
#include "error.h"


std::vector<float> apeiron::load_vertices(std::string_view filename)
{
  tinyobj::attrib_t attrib;
  std::vector<tinyobj::shape_t> shapes;
  std::vector<tinyobj::material_t> materials;
  std::string error;
  if (!tinyobj::LoadObj(&attrib, &shapes, &materials, &error, std::string{filename}.c_str())) {
    throw Error{error};
  }

  std::vector<float> vertices;
  for (std::size_t s=0; s<shapes.size(); ++s) {
    std::size_t index_offset = 0;
    for (std::size_t f=0; f<shapes[s].mesh.num_face_vertices.size(); ++f) {
      auto fv = shapes[s].mesh.num_face_vertices[f];
      for (std::size_t v=0; v<fv; ++v) {
        tinyobj::index_t idx = shapes[s].mesh.indices[index_offset + v];
        tinyobj::real_t vx = attrib.vertices[3*idx.vertex_index+0];
        tinyobj::real_t vy = attrib.vertices[3*idx.vertex_index+1];
        tinyobj::real_t vz = attrib.vertices[3*idx.vertex_index+2];
        vertices.push_back(vx);
        vertices.push_back(vy);
        vertices.push_back(vz);
      }
      index_offset += fv;
    }
  }

  return vertices;
}
